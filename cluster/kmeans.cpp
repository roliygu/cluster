#include "kmeans.h"

void KMeans::selectKPointsByRandom(Matrix &m, int k){
    size_t dim = this->dimension;

    size_t* index = Random::randIndex(m.m.size(), false);

    for(size_t i=0;i!=k;i++){

        double* tmp;
        try{
            // 这里new的内存直到kmeans运行完才释放
            tmp = new double[dim];
        }catch(bad_alloc &memExp) {
            cerr<<memExp.what()<<endl;
        }

        tmp = Memory::copyArray(m.m[index[i]], tmp, dim);
        this->barycenter.push_back(tmp);
    }

    delete[] index;

    return;
}

int KMeans::markPoint(double* point){

    double min;
    size_t label;

    for(size_t i=0;i!=this->barycenter.size();i++){
        if(i == 0){
            min = this->disF(point, this->barycenter[0], this->dimension);
            label = 0;
        }else{
            double d = this->disF(point, this->barycenter[i], this->dimension);
            if(d < min){
                min = d;
                label = i;
            }
        }
    }

    kPoints[label].push_back(point);
    return label;
}

void KMeans::markAllPoints(Matrix &m){

    // 重新分配点之前,将kPoints中所有点清空
    for(auto& i : this->kPoints){
        i.second.clear();
    }

    for(auto i : m.m){
        markPoint(i);
    }
}

double KMeans::updateKPoints(){

    double sum = 0;

    for(auto& i : this->kPoints){
        double* target = this->barycenter[i.first];
        this->barF(i.second, target, this->dimension);
        sum += this->disF(i.second[0], target, this->dimension);
    }
    return sum;
}

void KMeans::fit(Matrix &matrix){

    this->selectKPointsByRandom(matrix, this->K);

    double diff;
    do{
        markAllPoints(matrix);
        diff = updateKPoints();
    }while(diff>1);

    this->labels.clear();
    this->inertia = -1;

    return;
}

vector<size_t> KMeans::getLabels(Matrix &matrix){

    if(this->labels.size() == 0){
        map<intptr_t, size_t>* t = matrix.getIdMap();
        for(auto i : this->kPoints){
            for(auto j : i.second){
                size_t index = (*t)[*j];
                this->labels[index] = i.first;
            }
        }
        return this->labels;
    }else{
        return this->labels;
    }
}

double KMeans::getInertia(){
    if(this->inertia<0){
        this->inertia = totalErrFunc(this->kPoints);
    }
    return this->inertia;
}
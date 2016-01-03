#include "kmeans.h"

void KMeans::selectKPointsByRandom(Matrix &m, int k){
    size_t dim = dimension;

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
        barycenter.push_back(tmp);
    }

    delete[] index;

    return;
}

int KMeans::markPoint(double* point){

    double min;
    size_t label;

    for(size_t i=0;i!=barycenter.size();i++){
        if(i == 0){
            min = disF(point, barycenter[0], dimension);
            label = 0;
        }else{
            double d = disF(point, barycenter[i], dimension);
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
    for(auto &i : kPoints){
        i.second.clear();
    }

    for(auto i : m.m){
        markPoint(i);
    }
}

double KMeans::updateKPoints(){

    double sum = 0;

    for(auto &i : kPoints){
        double* target = barycenter[i.first];
        if(i.second.empty()){
            // 出现空簇
            kPoints.erase(i.first);
            continue;
        }
        barF(i.second, target, dimension);
        sum += disF(i.second[0], target, dimension);
    }
    return sum;
}

void KMeans::fit(Matrix &matrix){

    selectKPointsByRandom(matrix, K);

    double diff;
    do{
        markAllPoints(matrix);
        diff = updateKPoints();
    }while(diff>1);

    labels.clear();
    inertia = -1;

    return;
}

vector<size_t> KMeans::getLabels(Matrix &matrix){

    if(labels.size() == 0){
        labels = vector<size_t>(matrix.m.size());
        map<intptr_t, size_t>& t = matrix.getIdMap();
        for(auto i : kPoints){
            for(auto j : i.second){
                size_t index = t[(intptr_t) j];
                labels[index] = i.first;
            }
        }
        return labels;
    }else{
        return labels;
    }
}

double KMeans::getInertia(){
    if(inertia<0){
        inertia = totalErrFunc(kPoints);
    }
    return inertia;
}
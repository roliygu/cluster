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
        barycenter[i] = tmp;
    }

    delete[] index;

    return;
}

double KMeans::updateKPoints(){

    double sum = 0;
    double* target = new double[dimension];

    for(auto i : kPoints){

        double* source = barycenter[i.first];

        Memory::copyArray(source, target, dimension);

        if(i.second.empty()){
            // 出现空簇
            kPoints.erase(i.first);
            barycenter.erase(i.first);
            continue;
        }
        barF(i.second, source, dimension);
        sum += disF(source, target, dimension);
    }
    delete[] target;
    return sum;
}

void KMeans::fit(Matrix &matrix){

    selectKPointsByRandom(matrix, K);

    double diff;
    do{
        distributeAllPoints(matrix);
        diff = updateKPoints();
    }while(diff>1);

    labels.clear();
    inertia = -1;

    return;
}
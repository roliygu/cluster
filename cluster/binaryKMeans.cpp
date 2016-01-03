#include "binaryKMeans.h"

void BinaryKMeans::fit(Matrix &matrix){

    kPoints[0] = matrix.m;
    barycenter.push_back(new double[dimension]);
    barF(kPoints[0], barycenter[0], dimension);

    while(currentK!=K){
        splitKPoints();
        currentK++;
    }

}

vector<size_t> BinaryKMeans::getLabels(Matrix &matrix){

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

double BinaryKMeans::getInertia(){
    if(inertia<0){
        inertia = totalErrFunc();
    }
    return inertia;
}

void BinaryKMeans::splitKPoints(){

    size_t label;

    if(currentK==1){
        label = 0;
    } else{
        label = getMaxSSECluster();
    }

    vector<double*> two[2];

    split(kPoints[label], two);
    kPoints.erase(label);


    kPoints[label] = two[0];
    barF(kPoints[label], barycenter[label], dimension);

    kPoints[currentK] = two[1];
    barycenter.push_back(new double[dimension]);
    barF(kPoints[currentK], barycenter[currentK], dimension);
}

void BinaryKMeans::split(vector<double*> &points, vector<double*>*target){

    size_t max_c = Statistics::getMaxSDCol(points, dimension);
    double avg = Statistics::avgCol(points, max_c);

    for(size_t i=0;i!=points.size();i++){
        if(points[i][max_c]<avg){
            target[0].push_back(points[i]);
        }else{
            target[1].push_back(points[i]);
        }
    }
}
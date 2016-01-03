#include "cluster.h"

double Cluster::errFunc(vector<double*> &points, double *center){
    double res = 0;
    if(points.size()>0){
        for(size_t j=0;j!=points.size();j++){
            res += this->disF(center, points[j], dimension);
        }
    }
    return res;
}

double Cluster::totalErrFunc(){
    double sum = 0;
    for(auto& i : kPoints){
        sum += errFunc(i.second, barycenter[i.first]);
    }
    return sum;
}

void Cluster::fit(Matrix &matrix){
    return;
}

vector<size_t> Cluster::getLabels(Matrix &matrix){
    return this->labels;
}

double Cluster::getInertia(){
    return this->inertia;
}

size_t Cluster::getMaxSSECluster(){

    double max_sse = -1;
    size_t label;
    for(auto i : kPoints){
        double t_sse = errFunc(i.second, barycenter[i.first]);
        if(t_sse>max_sse){
            label = i.first;
            max_sse = t_sse;
        }
    }
    return label;
}
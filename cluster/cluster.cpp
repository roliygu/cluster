#include "cluster.h"

double Cluster::errFunc(vector<double*> &points){
    double res = 0;
    if(points.size()>0){
        for(size_t j=0;j!=points.size();j++){
            res += this->disF(points[0], points[j], dimension);
        }
    }
    return res;
}

double Cluster::totalErrFunc(map<size_t, vector<double*>> &kPoints){
    double sum = 0;
    for(auto& i : kPoints){
        sum += this->errFunc(i.second);
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
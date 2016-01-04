#include "cluster.h"

double Cluster::errFunc(vector<double*> points, double *center){
    double res = 0;
    if(points.size()>0){
        for(size_t j=0;j!=points.size();j++){
            res += disF(center, points[j], dimension);
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
    if(labels.size() == 0){
        labels = vector<size_t>(matrix.m.size());
        map<intptr_t, size_t>& t = matrix.getIdMap();
        for(auto i : kPoints){
            for(auto j : i.second){
                size_t index = t[(intptr_t) j];
                labels[index] = i.first;
            }
        }
    }
    return labels;
}

double Cluster::getInertia(){
    if(inertia<0){
        inertia = totalErrFunc();
    }
    return inertia;
}

size_t Cluster::getMaxSSECluster(){

    double max_sse = -1;
    size_t label;
    for(auto &i : kPoints){
        double t_sse = errFunc(i.second, barycenter[i.first]);
        if(t_sse>max_sse){
            label = i.first;
            max_sse = t_sse;
        }
    }
    return label;
}

void Cluster::generateNextPoint(size_t currentK){

    size_t maxLabel = currentK==1?0:getMaxSSECluster();

    vector<double*> two[2];
    split(kPoints[maxLabel], two);

    try{
        barycenter[currentK] = new double[dimension];
    }catch (const bad_alloc&e){
        cout<<"内存不足"<<endl;
        return;
    }

    barF(two[0], barycenter[maxLabel], dimension);
    barF(two[1], barycenter[currentK], dimension);

    kPoints.erase(maxLabel);
    kPoints[maxLabel] = two[0];
    kPoints[currentK] = two[1];
}

void Cluster::split(vector<double*> points, vector<double*>*target){

    size_t maxSDC = Statistics::getMaxSDCol(points, dimension);
    double avg = Statistics::avgCol(points, maxSDC);

    for(size_t i=0;i!=points.size();i++){
        if(points[i][maxSDC]<avg){
            target[0].push_back(points[i]);
        }else{
            target[1].push_back(points[i]);
        }
    }
}

void Cluster::distributeAllPoints(Matrix &m){
    for(auto &i : kPoints){
        i.second.clear();
    }
    for(auto i : m.m){
        distributePoint(i);
    }
}


int Cluster::distributePoint(double* point){

    double min=-1;
    size_t label;

    for(auto i : barycenter){
        if(min<0){
            min = disF(point, i.second, dimension);
            label = i.first;
        }else{
            double d = disF(point, i.second, dimension);
            if(d < min){
                min = d;
                label = i.first;
            }
        }
    }

    kPoints[label].push_back(point);
    return label;
}
#include "cluster.h"

namespace Cluster{

    /**
     * 每个数据的维数
     */
    int D=-1;

    void setD(int d){
        D = d;
    }

    map<int, vector<double*>> kMeans(Matrix &m, int k){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        map<int, vector<double*>> kPoints = selectKPoints(m, k, selectKPointsByRandom);
        double diff;
        do{
            markAllPoints(m, kPoints, calED);
            diff = updateKPoints(kPoints, calBarycenter, calED);
        }while(diff>1);

        return kPoints;
    };

    vector<double*> selectKPointsByRandom(Matrix &m, int k){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        size_t* index = Random::randIndex(m.m.size(), false);
        vector<double*> res;
        for(size_t i=0;i!=k;i++){
            // 这里new的点在update的时候会被回收
            double* tmp = Memory::copyArray(m.m[index[i]], D);
            res.push_back(tmp);
        }
        delete[] index;
        return res;
    }

    map<int, vector<double*>> selectKPoints(Matrix &m, int k, vector<double*> (*f)(Matrix &m, int t)){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        vector<double*> kPoints = f(m, k);

        map<int, vector<double*>> res;

        for(int i=0;i!=k;i++){
            res[i].push_back(kPoints[i]);
        }
        return res;
    };

    double getDistance(double* a, double* b,
                       double (*p)(double* a, double* b)){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        return p(a, b);
    }

    double calED(double* a, double* b){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        double sum = 0.0;
        for(int i=0;i!=D;i++){
            sum += (b[i]-a[i])*(b[i]-a[i]);
        }
        return sqrt(sum);
    }

    int markPoint(double* point, map<int, vector<double*> > &kPoints,
                  double (*p)(double* a, double* b)){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        double min=-1;
        int label;
        for(auto& i : kPoints){
            if(min<0){
                min = p(point, (i.second)[0]);
                label = i.first;
            }else{
                double d = p(point, (i.second)[0]);
                if(d<min){
                    min = d;
                    label = i.first;
                }
            }
        }
        kPoints[label].push_back(point);
        return label;
    }

    void markAllPoints(Matrix &m, map<int, vector<double*> > &kPoints,
                       double (*p)(double* a, double* b)){
        // 重新分配点之前,将kPoints中非质心点去掉
        for(auto& i : kPoints){
            vector<double*>* tmp = &(i.second);
            if(tmp->size()>1){
                tmp->erase(tmp->begin()+1,tmp->end());
            }
        }

        for(auto i : m.m){
            markPoint(i, kPoints, p);
        }
    }

    /**
     * 这个函数new的点在update的时候会被回收;
     * vector的第一个点有特殊含义,不参与计算重心
     */
    double* calBarycenter(vector<double*> &points){
        if(D==-1){
            throw invalid_argument("D is missing");
        }

        double* res = new double[D];

        for(size_t i=0;i!=D;i++){
            res[i] = points[1][i];
        }
        for(size_t i=2;i!=points.size();i++){
            for(size_t j=0;j!=D;j++){
                res[j] += points[i][j];
            }
        }
        for(size_t i=0;i!=D;i++){
            res[i] /= points.size()-1;
        }

        return res;
    }

    double updateKPoints(map<int, vector<double*> > &kPoints,
                         double* (*f)(vector<double*> &p),
                         double (*p)(double* a, double* b)){
        if(D==-1){
            throw invalid_argument("D is missing");
        }
        double sum = 0;
        for(auto& i : kPoints){
            double *tmp = f(i.second);
            sum += p(i.second[0], tmp);
            delete[] i.second[0];
            i.second[0] = tmp;
        }
        return sum;
    }

    double errFunc(map<int, vector<double*>> &kPoints, double (*p)(double* a, double* b)){
        double sum = 0;
        for(auto& i : kPoints){
            vector<double*> *tmp = &i.second;
            if(tmp->size()>1){
                for(size_t j=1;j!=tmp->size();j++){
                    sum += p(tmp->at(0), tmp->at(j));
                }
            }
        }
        return sqrt(sum);
    }
}


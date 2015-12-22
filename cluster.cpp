#include "cluster.h"

namespace Cluster{

    Option *op = NULL;

    void setOption(Option *opt){
        op = opt;
    }

    void Option::setDisF(double (*p)(double* a, double* b)){
        this->disF = p;
    }

    void Option::setSelF(vector<double*> (*p)(Matrix &m, int t)){
        this->selF = p;
    }

    void Option::setBarF(double* (*p)(vector<double*> &points)){
        this->barF = p;
    }

    map<int, vector<double*>> kMeans(Matrix &m, int k){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        map<int, vector<double*>> kPoints = selectKPoints(m, k);
        double diff;
        do{
            markAllPoints(m, kPoints);
            diff = updateKPoints(kPoints);
        }while(diff>1);

        return kPoints;
    };

    map<int, vector<double*>> selectKPoints(Matrix &m, int k){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        vector<double*> kPoints = op->selF(m, k);

        map<int, vector<double*>> res;

        for(int i=0;i!=k;i++){
            res[i].push_back(kPoints[i]);
        }
        return res;
    };

    vector<double*> selectKPointsByRandom(Matrix &m, int k){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        size_t* index = Random::randIndex(m.m.size(), false);
        vector<double*> res;
        for(size_t i=0;i!=k;i++){
            // 这里new的点在update的时候会被回收
            double* tmp = Memory::copyArray(m.m[index[i]],op->D);
            res.push_back(tmp);
        }
        delete[] index;
        return res;
    }

    double getDistance(double* a, double* b){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        return op->disF(a, b);
    }

    double calED(double* a, double* b){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        double sum = 0.0;
        for(int i=0;i!=op->D;i++){
            sum += (b[i]-a[i])*(b[i]-a[i]);
        }
        return sqrt(sum);
    }

    int markPoint(double* point, map<int, vector<double*> > &kPoints){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        double min=-1;
        int label;
        for(auto& i : kPoints){
            if(min<0){
                min = op->disF(point, (i.second)[0]);
                label = i.first;
            }else{
                double d = op->disF(point, (i.second)[0]);
                if(d<min){
                    min = d;
                    label = i.first;
                }
            }
        }
        kPoints[label].push_back(point);
        return label;
    }

    void markAllPoints(Matrix &m, map<int, vector<double*> > &kPoints){
        // 重新分配点之前,将kPoints中非质心点去掉
        for(auto& i : kPoints){
            vector<double*>* tmp = &(i.second);
            if(tmp->size()>1){
                tmp->erase(tmp->begin()+1,tmp->end());
            }
        }

        for(auto i : m.m){
            markPoint(i, kPoints);
        }
    }

    /**
     * 这个函数new的点在update的时候会被回收;
     * vector的第一个点有特殊含义,不参与计算重心
     */
    double* calBarycenter(vector<double*> &points){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }

        double* res = new double[op->D];

        for(size_t i=0;i!=op->D;i++){
            res[i] = points[1][i];
        }
        for(size_t i=2;i!=points.size();i++){
            for(size_t j=0;j!=op->D;j++){
                res[j] += points[i][j];
            }
        }
        for(size_t i=0;i!=op->D;i++){
            res[i] /= points.size()-1;
        }

        return res;
    }

    double updateKPoints(map<int, vector<double*> > &kPoints){
        if(op==NULL){
            throw invalid_argument("Option is missing.");
        }
        double sum = 0;
        for(auto& i : kPoints){
            double *tmp = op->barF(i.second);
            sum += op->disF(i.second[0], tmp);
            delete[] i.second[0];
            i.second[0] = tmp;
        }
        return sum;
    }

    double errFunc(map<int, vector<double*>> &kPoints){
        double sum = 0;
        for(auto& i : kPoints){
            vector<double*> *tmp = &i.second;
            if(tmp->size()>1){
                for(size_t j=1;j!=tmp->size();j++){
                    sum += op->disF(tmp->at(0), tmp->at(j));
                }
            }
        }
        return sqrt(sum);
    }
}


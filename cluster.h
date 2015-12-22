#ifndef CLUSTER_ANALYSIS_CLUSTER_H
#define CLUSTER_ANALYSIS_CLUSTER_H

#include <map>
#include <stdexcept>
#include <cstring>
#include <math.h>
#include "utils/utils.h"
#include "Matrix.h"


using std::vector;
using std::map;
using std::invalid_argument;

namespace Cluster{

    /**
     * k均值分类
     */
    map<int, vector<double*>> kMeans(Matrix &m, int k);

    /**
     * 选出K个点作为代表点,决定的方法由参数f决定
     */
    map<int, vector<double*> > selectKPoints(Matrix &m, int k);

    /**
     * 挑选k个点得一种实现方式,随机挑选k个点
     */
    vector<double*> selectKPointsByRandom(Matrix &m, int k);

    /**
     * 计算两个点之间的距离,距离计算方式由参数p决定
     */
    double getDistance(double* a, double* b);

    /**
     * 计算欧式距离
     */
    double calED(double* a, double* b);

    /**
     * 判断point离k个点中哪个点最近,并将该点分配到map中
     */
    int markPoint(double* point, map<int, vector<double*> > &kPoints);

    /**
     * 将matrix中所有点重新分配一遍
     */
    void markAllPoints(Matrix &m, map<int, vector<double*> > &kPoints);

    /**
     * 计算这堆点的质心
     */
    double* calBarycenter(vector<double*> &points);

    /**
     * 更新map中所有组的重心,并返回所有重心更新前后距离之和
     */
    double updateKPoints(map<int, vector<double*> > &kPoints);

    /**
     * 计算误差和
     */
    double errFunc(map<int, vector<double*>> &kPoints);

    /**
     * 聚类算法的配置
     */
    class Option{
    public:
        int D;
        double (*disF)(double* a, double* b);
        vector<double*> (*selF)(Matrix &m, int t);
        double* (*barF)(vector<double*> &points);

        Option(int d){
            this->D = d;
            this->disF = calED;
            this->selF = selectKPointsByRandom;
            this->barF = calBarycenter;
        }
        void setDisF(double (*p)(double* a, double* b));

        void setSelF(vector<double*> (*p)(Matrix &m, int t));

        void setBarF(double* (*p)(vector<double*> &points));
    };

    void setOption(Option *op);
}

#endif //CLUSTER_ANALYSIS_CLUSTER_H

#ifndef CLUSTER_ANALYSIS_CLUSTER_H
#define CLUSTER_ANALYSIS_CLUSTER_H

#include <map>
#include <stdexcept>
#include <cstring>
#include <math.h>
#include "utils/utils.h"
#include "Matrix.h"
#include <algorithm>


using std::vector;
using std::map;
using std::invalid_argument;
using std::sort;

namespace Cluster{

    /**
     * k均值聚类
     */
    map<int, vector<double*>> kMeans(Matrix &m, int k);

    /**
     * 二分k均值聚类
     */
    map<int, vector<double*>> binaryKMeans(Matrix &m, int k);

    /**
     * 选择SSE最大的一个簇,拆分成两个
     */
    void splitKPoints(map<int, vector<double*>> &kPoints);

    /**
     * 将一个簇分裂成两个簇:根据标准差最大的一维均分成两堆
     */
    vector<double*>* split(vector<double*> &points);

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
     * 计算一个簇的SEE
     */
    double errFunc(vector<double*> &points);

    /**
     * 计算所有簇的SEE
     */
    double totalErrFunc(map<int, vector<double*>> &kPoints);

    /**
     * 获取最大SSE的簇标号
     */
    int getMaxSSECluster(map<int, vector<double*>> &kPoints);


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

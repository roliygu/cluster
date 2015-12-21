#ifndef CLUSTER_ANALYSIS_CLUSTER_H
#define CLUSTER_ANALYSIS_CLUSTER_H

#include "Matrix.h"
#include <map>

using std::vector;
using std::map;

namespace Cluster{

    /**
     * 设定每个数据点的维度
     */
    void setD(int d);

    /**
     * k均值分类
     */
    map<int, vector<double*>> kMeans(Matrix &m, int k);

    /**
     * 选出K个点作为代表点,决定的方法由参数f决定
     */
    map<int, vector<double*> > selectKPoints(Matrix &m, int k, vector<double*> (*f)(Matrix &m, int t));

    /**
     * 挑选k个点得一种实现方式,随机挑选k个点
     */
    vector<double*> selectKPointsByRandom(Matrix &m, int k);

    /**
     * 计算两个点之间的距离,距离计算方式由参数p决定
     */
    double getDistance(double* a, double* b,
                       double (*p)(double* a, double* b));

    // 计算欧式距离
    double calED(double* a, double* b);

    // 判断point离k个点中哪个点最近,并将该点分配到map中
    int markPoint(double* point, map<int, vector<double*> > &kPoints,
                  double (*p)(double* a, double* b));

    /**
     * 将matrix中所有点重新分配一遍
     */
    void markAllPoints(Matrix &m, map<int, vector<double*> > &kPoints,
                       double (*p)(double* a, double* b));

    // 计算这堆点的重心
    double* calBarycenter(vector<double*> &points);

    // 更新map中所有组的重心,并返回所有重心更新前后距离之和
    double updateKPoints(map<int, vector<double*> > &kPoints,
                         double* (*f)(vector<double*> &p),
                         double (*p)(double* a, double* b));

    double errFunc(map<int, vector<double*>> &kPoints, double (*p)(double* a, double* b));
}

#endif //CLUSTER_ANALYSIS_CLUSTER_H

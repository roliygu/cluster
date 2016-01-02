#ifndef CLUSTER_KMEANS_H
#define CLUSTER_KMEANS_H

#include "cluster.h"

class KMeans : public Cluster{
public:

    KMeans(size_t dim, size_t k):Cluster(dim),K(k){}

    virtual void fit(Matrix &matrix);

    virtual vector<size_t> getLabels(Matrix &matrix);

    virtual double getInertia();

protected:

    size_t K;

    /**
    * 挑选k个点的一种实现方式,随机挑选k个点
    */
    void selectKPointsByRandom(Matrix &m, int k);

    /**
    * 判断point离k个点中哪个点最近,并将该点分配到map中
    */
    int markPoint(double* point);

    /**
    * 将matrix中所有点重新分配一遍
    */
    void markAllPoints(Matrix &m);

    /**
     * 更新map中所有组的重心,并返回所有重心更新前后距离之和
     */
    double updateKPoints();
};


#endif //CLUSTER_KMEANS_H

#ifndef CLUSTER_BINARYKMEANS_H
#define CLUSTER_BINARYKMEANS_H

#include "cluster.h"

class BinaryKMeans : public Cluster{
public:
    BinaryKMeans(size_t dim, size_t k):Cluster(dim),K(k),currentK(1){}

    virtual void fit(Matrix &matrix);

    virtual vector<size_t> getLabels(Matrix &matrix);

    virtual double getInertia();

private:
    size_t K;

    size_t currentK;

    /**
    * 选择SSE最大的一个簇,拆分成两个
    */
    void splitKPoints();

    /**
     * 将一个簇分裂成两个簇:根据标准差最大的一维均分成两堆
     */
    void split(vector<double*> &points, vector<double*>*target);


};


#endif //CLUSTER_BINARYKMEANS_H

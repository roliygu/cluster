#ifndef CLUSTER_BINARYKMEANS_H
#define CLUSTER_BINARYKMEANS_H

#include "cluster.h"

class BinaryKMeans : public Cluster{
public:
    BinaryKMeans(size_t dim, size_t k):Cluster(dim),K(k),currentK(1){}

    virtual void fit(Matrix &matrix);

private:
    size_t K;

    size_t currentK;
};


#endif //CLUSTER_BINARYKMEANS_H

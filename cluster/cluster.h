#ifndef CLUSTER_CLUSTER_H
#define CLUSTER_CLUSTER_H

#include <stdexcept>
#include <map>
#include "Math.h"
#include "../matrix/Matrix.h"
#include "../utils/utils.h"

using std::bad_alloc;
using std::cerr;
using std::map;

class Cluster {
public:

    Cluster(size_t dim):dimension(dim),inertia(-1),disF(DataMining::calED),barF(DataMining::calBarycenter){}

    virtual void fit(Matrix &matrix);

    virtual vector<size_t> getLabels(Matrix &matrix);

    virtual double getInertia();

protected:

    /***********Data members***********/

    size_t dimension;

    vector<double*> barycenter;

    map<size_t, vector<double*>> kPoints;

    vector<size_t> labels;

    double inertia;

    /**
    * 距离函数
    */
    double (*disF)(double* a, double* b, size_t dim);

    /**
    * 质心函数
    */
    void (*barF)(vector<double*> &points, double* res, size_t dim);

    /***********Function members***********/

    /**
    * 计算一个簇的SEE
    */
    double errFunc(vector<double*> &points);

    /**
     * 计算所有簇的SEE
     */
    double totalErrFunc(map<size_t, vector<double*>> &kPoints);
};


#endif //CLUSTER_CLUSTER_H

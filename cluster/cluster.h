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

    vector<size_t> getLabels(Matrix &matrix);

    double getInertia();

    map<size_t, vector<double*>> kPoints;

    map<size_t, double*> barycenter;

protected:

    /***********Data members***********/

    size_t dimension;





    vector<size_t> labels;

    double inertia;

    /**
    * 距离函数
    */
    double (*disF)(double* a, double* b, size_t dim);

    /**
    * 质心函数
    */
    void (*barF)(vector<double*> points, double* res, size_t dim);

    /***********Function members***********/

    /**
    * 将matrix中所有点重新分配一遍
    */
    void distributeAllPoints(Matrix &m);

    /**
    * 判断point离k个点中哪个点最近,并将该点分配到map中
    */
    int distributePoint(double* point);

    /**
    * 计算一个簇的SEE
    */
    double errFunc(vector<double*> points, double *center);

    /**
     * 计算所有簇的SEE
     */
    double totalErrFunc();

    /**
     * 获取最大SSE的簇标号
     */
    size_t getMaxSSECluster();

    /**
    * 通过拆分最大SSE簇的方式生成新的簇
    */
    void generateNextPoint(size_t currentK);

    /**
     * 将一个簇分裂成两个簇:根据标准差最大的一维均分成两堆
     */
    void split(vector<double*> points, vector<double*>*target);
};


#endif //CLUSTER_CLUSTER_H

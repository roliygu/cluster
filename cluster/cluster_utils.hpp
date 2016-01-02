#ifndef CLUSTER_CLUSTER_UTILS_HPP
#define CLUSTER_CLUSTER_UTILS_HPP

#include <vector>

using std::vector;

/**
* 计算欧式距离
*/
double calED(double* a, double* b, size_t dim){
    double sum = 0.0;

    for(size_t i=0;i!=dim;i++){
        sum += (b[i]-a[i])*(b[i]-a[i]);
    }
    return sqrt(sum);
}

/**
* 计算这堆点的质心
*/
void calBarycenter(vector<double*> &points, double* res, size_t dim){

    for(size_t i=0;i!=dim;i++){
        res[i] = points[0][i];
    }
    for(size_t i=1;i!=points.size();i++){
        for(size_t j=0;j!=dim;j++){
            res[j] += points[i][j];
        }
    }
    for(size_t i=0;i!=dim;i++){
        res[i] /= points.size()-1;
    }

    return;
}



#endif
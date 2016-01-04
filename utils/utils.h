#ifndef CLUSTER_ANALYSIS_UTILS
#define CLUSTER_ANALYSIS_UTILS

#include <cstring>
#include <random>
#include <iostream>
#include <time.h>
#include <stdexcept>

using std::cout;
using std::endl;
using std::invalid_argument;
using std::vector;

namespace Random{

    /**
     * 以当前时间设置随机种子
     */
    inline void setNewSeed();

    /**
     * 根据给定的值设定随机种子
     */
    inline void setSeed(unsigned seed);

    /**
     * 生成[0,size)的序列,返回打乱顺序后的结果
     */
    size_t* randIndex(size_t size, bool newSeed);

    /**
     * 随机生成[a,b)之间的一个整数
     */
    int randint(int a, int b, bool newSeed);

    /**
     * 随机从array中抽取一个元素
     */
    template<class T>
    T choice(T* array, size_t size, bool newSeed){
        if(!array || size==0){
            throw invalid_argument("Invalid argument(array, size)");
        }
        if(newSeed){
            setNewSeed();
        }
        return array[rand()%size];
    }

    /**
     * 随机抽样k个元素,且每次抽取不放回
     */
    template<class T>
    bool sample(T* array, T* target, size_t size, size_t k, bool newSeed){
        if(array == NULL || target == NULL || size==0 || k==0 || k>size){
            throw invalid_argument("Invalid argument(array, target, size, k)");
        }
        size_t* index = randIndex(size, newSeed);
        for(size_t i=0;i!=k;i++){
            target[i] = array[i];
        }
        delete[] index;
        return true;
    }

    /**
    * 打乱array中所有元素
    */
    template<class T>
    bool shuffle(T* array, T* target, size_t size, bool newSeed){
        return sample(array, target, size, size, newSeed);
    }

    /**
     * 随机抽样k个元素,且每次抽取都放回
     */
    template<class T>
    bool sampleAndBack(T* array, T* target, size_t size, size_t k, bool newSeed){
        if(array == NULL || target == NULL || size==0 || k==0 || k>size){
            throw invalid_argument("Invalid argument(array, target, size, k)");
        }
        for(size_t i=0;i!=k;i++){
            target[i] = choice(array, size, newSeed);
        }
        return true;
    }
}

namespace Memory{

    /**
     * 拷贝一个数组,如果数组的元素是指针的话,并不复制指针指向的内容
     */
    template<class T>
    T* copyArray(T* source, T* target, size_t size){
        if(source == NULL){
            throw invalid_argument("Invalid argument(source)");
        }
        return (T*) memcpy(target, source, sizeof(T)*size);
    }

}

namespace Statistics{

    /**
     * 计算某列的平均数
     */
    template<class T>
    double avgCol(vector<T*> &data, size_t col){
        double res = 0.0;
        for(auto i : data){
            res += i[col];
        }
        return res/data.size();
    }

    /**
     * 计算某列的标准差
     */
    template<class T>
    double sdCol(vector<T*> &data, size_t col){
        double avg = avgCol(data, col);
        double res = 0.0;
        for(auto i : data){
            res += (i[col]-avg)*(i[col]-avg);
        }
        return sqrt(res/data.size());
    }

    /**
     * 得到标准差最大的列index
     */
    template<class T>
    size_t getMaxSDCol(vector<T*> &data, size_t d){
        size_t maxSDC;
        double sd;
        for(size_t i=0;i!=d;i++){
            if(i==0){
                maxSDC = 0;
                sd = Statistics::sdCol(data, 0);
            }else{
                double t_sd = Statistics::sdCol(data, i);
                if(t_sd>sd){
                    maxSDC = i;
                    sd = maxSDC;
                }
            }
        }
        return maxSDC;
    }
}

namespace Time{

    /**
     * 返回当前时刻与上一次调用时的时间,如果是第一次调用,返回的是纪元秒
     */
    double passed();

}

namespace DataMining{

    /**
    * 计算欧式距离
    */
    template <class T>
    double calED(T* a, T* b, size_t dim){
        double sum = 0.0;

        for(size_t i=0;i!=dim;i++){
            sum += (b[i]-a[i])*(b[i]-a[i]);
        }
        return sqrt(sum);
    }

    /**
    * 计算这堆点的质心
    */
    template <class T>
    void calBarycenter(vector<T*> points, double* res, size_t dim){

        if(points.empty()){
            return;
        }

        if(points.size()==1){
            for(size_t i=0;i!=dim;i++){
                res[i] = points[0][i];
            }
            return;
        }

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

}

#endif //CLUSTER_ANALYSIS_UTILS
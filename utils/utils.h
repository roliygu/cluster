#ifndef CLUSTER_ANALYSIS_UTILS
#define CLUSTER_ANALYSIS_UTILS

#include <cstring>
#include <random>
#include <iostream>
#include <time.h>

using std::cout;
using std::endl;
using std::invalid_argument;

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

    template<class T>
    T* copyArray(T* source, size_t size){
        if(source == NULL){
            throw invalid_argument("Invalid argument(source)");
        }
        T* res = new T[size];
        return (T*) memcpy(res, source, sizeof(T)*size);
    }

}

namespace Time{

    /**
     * 返回当前时刻与上一次调用时的时间,如果是第一次调用,返回的是纪元秒
     */
    double passed();

}

#endif //CLUSTER_ANALYSIS_UTILS
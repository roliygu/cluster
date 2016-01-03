#include <iostream>
#include <vector>
#include "../utils/utils.h"
#include "../cluster/kmeans.h"
#include "../cluster/binaryKMeans.h"
#include "../data/data.h"

int main() {

    //1. 获取测试数据
    Matrix data = getData1();

    //2. 设置聚类参数,比如维度和K
    Cluster *kmeans = new KMeans(100, 10);

    //3. 运行
    kmeans->fit(data);

    //4. 查看结果
    cout<<kmeans->getInertia()<<endl;
    vector<size_t> res = kmeans->getLabels(data);
    for(auto i : res){
        cout<<i<<" ";
    }

    // 或者使用二分K均值聚类
    Cluster *bKmeans = new BinaryKMeans(100, 10);

    bKmeans->fit(data);

    cout<<kmeans->getInertia()<<endl;
    res = kmeans->getLabels(data);
    for(auto i : res){
        cout<<i<<" ";
    }

    return 0;
}


#include <iostream>
#include <vector>
#include "../utils/utils.h"
#include "cluster.h"
#include "../data/data.h"

int main() {

    //1. 获取测试数据
    Matrix data = getData1();

    //2. 设置聚类算法的相关参数,这里的100是指data中每条数据的维度数
    Cluster::Option *op = new Cluster::Option(100);
    Cluster::setOption(op);

    //3. 使用基本kMeans将data分成4类,res的key是类标签,value是被分配的点的指针
    map<size_t, vector<double*>> res = Cluster::kMeans(data, 4);

    //4. (可选)data.y._group用来存储类标签,调用updateGroup更新_group字段
    data.updateGroup(res);

    //5. (可选)
    data.print();

    return 0;
}


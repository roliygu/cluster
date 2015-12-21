#include <iostream>
#include <vector>
#include "utils/utils.h"
#include "cluster.h"
#include "Matrix.h"
#include "data/data.h"

int main() {

    Time::passed();
    Matrix data = getData1();
    Cluster::setD(1000);
    map<int, vector<double*>> res = Cluster::kMeans(data, 2);
    cout<<Cluster::errFunc(res, Cluster::calED)<<endl;
    cout<<Time::passed()<<endl;
    return 0;
}


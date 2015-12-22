#include <iostream>
#include <vector>
#include "utils/utils.h"
#include "cluster.h"
#include "Matrix.h"
#include "data/data.h"

int main() {


    Matrix data = getData1();
    Cluster::Option *op = new Cluster::Option(100);
    Cluster::setOption(op);
    Time::passed();
    map<int, vector<double*>> res = Cluster::kMeans(data, 4);
    cout<<Cluster::totalErrFunc(res)<<endl;
    cout<<Time::passed()<<endl;

    Cluster::setOption(op);
    Time::passed();
    res = Cluster::binaryKMeans(data, 4);
    cout<<Cluster::totalErrFunc(res)<<endl;
    cout<<Time::passed()<<endl;

    return 0;
}


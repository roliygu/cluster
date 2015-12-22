#include <iostream>
#include <vector>
#include "utils/utils.h"
#include "cluster.h"
#include "Matrix.h"
#include "data/data.h"

int main() {

    Time::passed();
    Matrix data = getData1();
    Cluster::Option *op = new Cluster::Option(30000);
    Cluster::setOption(op);
    map<int, vector<double*>> res = Cluster::kMeans(data, 2);
    cout<<Cluster::totalErrFunc(res)<<endl;
    cout<<Time::passed()<<endl;


//    vector<int> *ap = new vector<int>();
//    vector<int> *bp = new vector<int>();
//    map<int, vector<int>> c;
//    c[0] = *ap;
//    c[0] = *bp;

    return 0;
}


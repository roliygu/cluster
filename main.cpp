#include <iostream>
#include <vector>
#include "utils/utils.h"
#include "cluster.h"
#include "Matrix.h"
#include "data/data.h"

int main() {

    Matrix data = getData1();

    map<uint64_t, long> m = data.add2id();

    map<int, vector<double*>> res,res2;
    Cluster::Option *op = new Cluster::Option(1000);
    Cluster::setOption(op);

//    Matrix data = getData1();
//    Cluster::Option *op = new Cluster::Option(100);
//    Cluster::setOption(op);
//    Time::passed();
//    map<int, vector<double*>> res = Cluster::kMeans(data, 4);
//    cout<<Cluster::totalErrFunc(res)<<endl;
//    cout<<Time::passed()<<endl;

//    data.print();
    Time::passed();
    res = Cluster::binaryKMeans(data, 100);
    cout<<Cluster::totalErrFunc(res)<<endl;
    cout<<Time::passed()<<endl;

//    for(auto i : res){
//        cout<<"label: "<<i.first<<" ";
//        for(size_t j=1;j!=i.second.size();j++){
//            cout<<m[(uint64_t)i.second[j]]<<", ";
//        }
//        cout<<endl;
//    }

    return 0;
}


#include <iostream>
#include <vector>
#include "utils/utils.h"
#include "cluster/cluster.h"
#include "data/data.h"

int main() {

    Matrix data = getData1();

    map<size_t, vector<double*>> res;
    Cluster::Option *op = new Cluster::Option(100);
    Cluster::setOption(op);

//    Matrix data = getData1();
//    Cluster::Option *op = new Cluster::Option(100);
//    Cluster::setOption(op);
//    Time::passed();
//    map<size_t, vector<double*>> res = Cluster::kMeans(data, 4);
//    cout<<Cluster::totalErrFunc(res)<<endl;
//    cout<<Time::passed()<<endl;

//    data.print();
    Time::passed();
    res = Cluster::binaryKMeans(data, 10);
    data.updateGroup(res);
    data.print();
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


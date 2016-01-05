#include <iostream>
#include "matrix/Matrix.h"
#include "data/data.h"
#include "cluster/kmeans.h"
#include "cluster/binaryKMeans.h"

using namespace std;

//void print(map<size_t, vector<double*>> m){
//    for(auto &i : m){
//        cout<<i.first<<endl;
//        for(auto j : i.second){
//            cout<<j[0]<<", "<<j[1]<<endl;
//        }
//    }
//}
//
//void printt(map<size_t, double*> barycenter){
//    cout<<"100"<<endl;
//    for(auto i : barycenter){
//        cout<<i.second[0]<<", "<<i.second[1]<<endl;
//    }
//}

int main() {

    Matrix data = getData1();

    data.print();

    size_t width = 2;

    size_t k = 3;

    Time::passed();

    Cluster* p = new BinaryKMeans(width, k);

    p->fit(data);

    print(p->kPoints);

    printt(p->barycenter);

    cout<<"costTime: "<<Time::passed()<<endl;

    cout<<"totalError: "<<p->getInertia()<<endl;

    vector<size_t> labels = p->getLabels(data);
    for(auto i : labels){
        cout<<i<<" ";
    }
    cout<<endl;

    Time::passed();

    Cluster* q = new KMeans(width, k);

    q->fit(data);

    print(q->kPoints);

    printt(q->barycenter);

    cout<<"costTime: "<<Time::passed()<<endl;

    cout<<"totalError: "<<q->getInertia()<<endl;

    vector<size_t> labels = q->getLabels(data);
    for(auto i : labels){
        cout<<i<<" ";
    }

    return 0;
}


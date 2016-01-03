#include <iostream>
#include "matrix/Matrix.h"
#include "data/data.h"
#include "cluster/kmeans.h"
#include "cluster/binaryKMeans.h"
#include "utils/utils.h"

using namespace std;


int main() {

    Matrix data = getData1();

    Time::passed();

    Cluster* p = new BinaryKMeans(10000, 100);

    p->fit(data);

    cout<<Time::passed()<<endl;

    cout<<p->getInertia()<<endl;
//
//    vector<size_t> label = p->getLabels(data);
//
//    for(auto i: label){
//        cout<<i<<", ";
//    }

    return 0;
}


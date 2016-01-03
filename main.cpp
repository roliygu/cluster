#include <iostream>
#include "matrix/Matrix.h"
#include "data/data.h"
#include "cluster/kmeans.h"

using namespace std;


int main() {

    Matrix data = getData1();

    //data.print();

    Cluster* p = new KMeans(10, 3);

    p->fit(data);

    cout<<p->getInertia()<<endl;

    vector<size_t> label = p->getLabels(data);

    for(auto i: label){
        cout<<i<<", ";
    }

    return 0;
}


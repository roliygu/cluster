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

//    Cluster* p = new BinaryKMeans(10000, 100);
//
//    p->fit(data);
//
//    cout<<Time::passed()<<endl;
//
//    cout<<p->getInertia()<<endl;

    Cluster* q = new KMeans(10000, 100);

    q->fit(data);

    cout<<Time::passed()<<endl;

    cout<<q->getInertia()<<endl;

    return 0;
}


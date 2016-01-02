#include <iostream>
#include "matrix/Matrix.h"
#include "data/data.h"
#include "cluster/kmeans.h"

using namespace std;


int main() {

    Matrix data = getData1();

    KMeans* p = new KMeans(10, 3);

    Cluster c = (*p);

    c.fit(data);

    cout<<c.getInertia()<<endl;

    return 0;
}


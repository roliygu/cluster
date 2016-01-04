#include "binaryKMeans.h"

void BinaryKMeans::fit(Matrix &matrix){

    kPoints[0] = matrix.m;

    try{
        barycenter[0] = new double[dimension];
    }catch (const bad_alloc& e){
        cout<<"内存不足"<<endl;
        return ;
    }

    barF(kPoints[0], barycenter[0], dimension);

    while(currentK!=K){
        generateNextPoint(currentK);
        distributeAllPoints(matrix);
        currentK++;
    }

}


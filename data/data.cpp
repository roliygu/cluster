//
// Created by Roliy on 15/12/17.
//
#include "data.h"

using std::vector;

Matrix getData1(){

    int size = 1000;
    
    Matrix data1;
    vector<HeaderItem> xHeader, yHeader;
    for(int i=0;i!=size;i++){
        HeaderItem t;
        t.setData(i, "1", -1);
        xHeader.insert(xHeader.end(), t);
        t.setData(-i, "2", -1);
        yHeader.insert(yHeader.end(), t);
    }

    data1.x = xHeader;
    data1.y = yHeader;

    for(int i=0;i!=size;i++){
        double *tmp = new double[size];
        for(int j=0;j!=size;j++){
            tmp[j] = rand()%100;
        }
        data1.m.insert(data1.m.end(), tmp);
    }

    return data1;
}


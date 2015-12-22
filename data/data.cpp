//
// Created by Roliy on 15/12/17.
//
#include "data.h"

using std::vector;
using std::bad_alloc;

Matrix getData1(){

    int size = 100;
    
    Matrix data1;
    vector<HeaderItem> xHeader, yHeader;
    for(int i=0;i!=size;i++){
        HeaderItem t;
        t.setData(-i, "1", -1);
        xHeader.insert(xHeader.end(), t);
        t.setData(i, "2", -1);
        yHeader.insert(yHeader.end(), t);
    }

    data1.x = xHeader;
    data1.y = yHeader;

    for(int i=0;i!=size;i++){
        double *tmp;
        try{
            tmp = new double[size];
        }catch(const bad_alloc&e){
            cout<<"内存不足"<<endl;
            return data1;
        }
        for(int j=0;j!=size;j++){
            tmp[j] = rand()%100;
        }
        data1.m.insert(data1.m.end(), tmp);
    }

    return data1;
}


#include "data.h"

using std::vector;
using std::bad_alloc;

Matrix getData1(){

    int size = 100;
    int width = 2;
    
    Matrix data1;
    vector<HeaderItem> yHeader;
    for(int i=0;i!=size;i++){
        HeaderItem t;
        t.setData(i, "2", -1);
        yHeader.insert(yHeader.end(), t);
    }

    data1.y = yHeader;
    data1.setD(width);

    for(int i=0;i!=size;i++){
        double *tmp;
        try{
            tmp = new double[width];
        }catch(const bad_alloc&e){
            cout<<"内存不足"<<endl;
            return data1;
        }
        for(int j=0;j!=width;j++){
            tmp[j] = rand()%100;
        }
        data1.m.push_back(tmp);
    }

    return data1;
}


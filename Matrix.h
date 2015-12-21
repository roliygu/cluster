
#ifndef CLUSTER_ANALYSIS_MATRIX_H
#define CLUSTER_ANALYSIS_MATRIX_H

#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class HeaderItem{
public:
    long _id;
    int _group;
    string _value;
    HeaderItem(long id, string value){
        this->_id = id;
        this->_value = value;
        this->_group = -1;
    };
    HeaderItem(){};
    void setData(long id, string value, int group);
    void print();
};

class Matrix{
public:
    vector<HeaderItem> x;
    vector<HeaderItem> y;
    vector<double*> m;
    void print();

    void setD(int d){this->D = d;}
    int getD(){return this->D;}

private:
    int D;

};


#endif //CLUSTER_ANALYSIS_MATRIX_H

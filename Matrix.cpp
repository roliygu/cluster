#include "Matrix.h"

void HeaderItem::print(){
    cout<<"{_id: "<<this->_id<<", _group:"<<this->_group<<", _value:"<<this->_value<<"}"<<endl;
}

void HeaderItem::setData(long id, string value, int group){
    this->_id = id;
    this->_value = value;
    this->_group = group;
}

void Matrix::print(){
    cout<<"{"<<endl;
    cout<<"x:"<<endl;
    for(int i=0;i!=this->x.size();i++){
        cout<<"    ";
        this->x[i].print();
    }
    cout<<"y:"<<endl;
    for(int i=0;i!=this->y.size();i++){
        cout<<"    ";
        this->y[i].print();
    }
    cout<<"m:"<<endl;
    for(int i=0;i!=this->x.size();i++){
        cout<<"    (";
        for(int j=0;j!=this->y.size();j++){
            cout<<this->m[i][j]<<", ";
        }
        cout<<")"<<endl;
    }
    cout<<"}"<<endl;
}
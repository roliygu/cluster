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

map<uint64_t, long> Matrix::add2id(){

    map<uint64_t, long> res;
    for(size_t i=0;i!=this->m.size();i++){
        res[(uint64_t)(this->m[i])] = this->y[i]._id;
    }
    return res;
};

//void Matrix::updateGroup(map<int, vector<double*>> kPoints){
//
//    if(this->idMap == nullptr){
//        this->idMap = add2id();
//    }
//    for(auto i : kPoints){
//        for(size_t j=1;j!=i.second.size();j++){
//            long tid = this->idMap[(uint64_t)i.second[j]];
//            this->y[tid]._group = i.first;
//        }
//    }
//
//}

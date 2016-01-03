
#ifndef CLUSTER_ANALYSIS_MATRIX_H
#define CLUSTER_ANALYSIS_MATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include <map>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::map;

class HeaderItem{
public:
    size_t _id;

    size_t _group;

    string _value;

    /********Function member********/

    HeaderItem(){};

    HeaderItem(size_t id, string value);

    void setData(size_t id, string value, size_t group);

    void print();
};

class Matrix{
public:

    vector<HeaderItem> y;

    vector<double*> m;

    /********Function member********/

    void print();

    void setD(int d){D = d;}

    int getD(){return D;}

    void updateGroup(map<size_t, vector<double*>> kPoints);

    map<intptr_t, size_t>& getIdMap();

private:

    int D;

    map<intptr_t, size_t> idMap;

    void setIdMap();
};


#endif //CLUSTER_ANALYSIS_MATRIX_H

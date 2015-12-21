#include "utils.h"

namespace Random{

    inline void setNewSeed(){
        srand((unsigned)time(NULL));
    }

    inline void setSeed(unsigned seed){
        srand(seed);
    }

    int randint(int a, int b, bool newSeed){
        if(a>b || a==b){
            cout<<"Invalid argument(a, b)"<<endl;
            return 0;
        }
        if(newSeed){
            setNewSeed();
        }
        return (rand()%(b-a))+a;
    }

    size_t* randIndex(size_t size, bool newSeed){
        if(size==0){
            cout<<"Invalid argument(size)"<<endl;
            return NULL;
        }
        if(newSeed){
            setNewSeed();
        }
        size_t* res = new size_t[size];
        for(size_t i=0;i!=size;i++){
            res[i] = i;
        }
        for(size_t i=0;i!=size;i++){
            int tmp = res[i];
            int target = rand()%size;
            res[i] = res[target];
            res[target] = tmp;
        }
        return res;
    }
}

namespace Memory{



}

namespace Time{

    clock_t last = 0;

    double passed(){
        clock_t current = clock(),tmp;
        tmp = last;
        last = current;
        return (double)(current-tmp)/CLOCKS_PER_SEC;
    }
}

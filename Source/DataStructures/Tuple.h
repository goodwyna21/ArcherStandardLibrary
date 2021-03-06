#ifndef TUPLE_H
#define TUPLE_H

/*
*/
#include "HashTable.h"
using namespace std;

template<typename T,size_t size=2>
struct Tuple{
    T elems[size];
    Tuple(){}
    Tuple(T foo, T bar){elems[0]=foo;elems[1]=bar;}
    T& operator[](size_t pos){return elems[pos];}
    Tuple<T>& operator= (Tuple<T,size> a){
        for(int i = 0; i < size; i++){
            elems[i]=a.elems[i];}
        return *this;
    }
    bool operator== (Tuple<T,size> a){
        return a.elems == elems;
    }
    bool operator!= (Tuple<T,size> a){
        return !((*this)==a);
    }
};

#endif

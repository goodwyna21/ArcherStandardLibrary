#ifndef HASHTABLE_H
#define HASHTABLE_H

/*
Provides a hash table struct which can store any number of
elements indexed by a type with a defined hashing function
(usually the index type is string). Hash tables theoretically
have an O(1) lookup time, compared to an array with complexity
O(n). They will not become slower the more elements are stored
inside of a table.

Unfortunately my implementation is not optimal and cannot be
resized, meaning eventually there will be stacks of elements in
the table and it will begin to slow down. I'm planning on adding
this soon, but for now the best approach is to initialize the
table with a sufficiently large size, however this does mean
more memory is used. I'm sure you can easily find or create a
better implementation if you need optimal speed and memory usage.
 */
#include "BinaryTree.h"
using namespace std;

template <class KeyT,class ValT>
struct HashNode{
    static HashNode<KeyT,ValT> * genNode(){
        HashNode<KeyT,ValT> * temp = new HashNode<KeyT,ValT>();
        return temp;
    }

    KeyT id;
    ValT val;
    HashNode * next;
    HashNode(){
        next=nullptr;
    }
    HashNode(KeyT i, ValT v){
        id = i;
        val = v;
        next = nullptr;
    }
    ~HashNode(){
        killChildren();
    }
    size_t attach(HashNode * h){
        if(next==nullptr){
            next = h;
            return 1;
        }else{
            return next->attach(h) + 1;
        }
    }

    void killChildren(){
        if(next==nullptr){
            return;
        }else{
            return next->killChildren();
        }
    }
};

const size_t DEFSIZE = 11;
template <typename KeyT,typename ValT, size_t Size=DEFSIZE>
struct HashTable{
    HashNode<KeyT,ValT> * array[Size];
    HashTable(){
        for(int i = 0; i < Size; i++){
            array[i] = nullptr;
        }
    }
    ~HashTable(){
        for(int i = 0; i < Size; i++){
            if(array[i]!=nullptr){
                array[i]->killChildren();
                delete array[i];
            }
        }
    }

    size_t genIndex(KeyT key){
        return hash<KeyT>()(key) % Size;
    }
    size_t push(KeyT key,ValT val){
        size_t ind = genIndex(key);
        if(array[ind]==nullptr){
            array[ind]=new HashNode<KeyT,ValT>(key,val);
            return 1;
        }else{
            return array[ind]->attach(new HashNode<KeyT,ValT>(key,val));
        }
    }
    ValT& get(KeyT key){
        size_t ind = genIndex(key);
        HashNode<KeyT,ValT> * pos = array[ind];
        if(pos==nullptr){
            throw exception("key not present");
        }
        while(pos->id != key){
            if(pos->next!=nullptr){
                pos = pos->next;
            }else{
                throw exception("key not present");
            }
        }
        return pos->val;
    }
    ValT& operator[] (KeyT key){
        return get(key);
    }
    string toString(){
        string ret = "Size: " + to_string(Size) + "\n";
        int maxSize = to_string(Size-1).size();
        HashNode<KeyT,ValT> * pos;
        for(int i = 0; i < Size; i++){
            if(array[i]!=nullptr){
                ret += to_string(i);
                for(int k = 0; k < maxSize - to_string(i).size(); k++){
                    ret += " ";
                }
                pos = array[i];
                while(pos != nullptr){
                    ret += " -> ";
                    ret += (pos->val);
                    pos = pos->next;
                }
                ret += "\n";
            }
        }
        return ret;
    }
};

#endif /* HASHTABLE_H */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iomanip>
#include "Vectors.h"
using namespace std;

/*
Provides a binary search tree struct which can store and quickly
search elements. A binary tree is very quick at checking if it
contains a certain value, making it useful for many applications.
Notably any duplicate elements are discarded.
*/

template <typename T>
struct treeNode{
    T val;
    treeNode * less;
    treeNode * more;
    treeNode(T obj){
        val = obj;
        less = nullptr;
        more = nullptr;
    }
    ~treeNode(){
        if(less!=nullptr){
            delete less;
        }
        if(more!=nullptr){
            delete more;
        }
    }
    bool attach(T obj){
        if(obj == val){return false;}
        if(obj < val){
            if(less == nullptr){
                less = new treeNode<T>(obj);
                return true;
            }
            return less->attach(obj);
        }
        if(more == nullptr){
            more = new treeNode<T>(obj);
            return true;
        }
        return more->attach(obj);
    }
    bool has(T obj){
        if(obj == val){return true;}
        if(less!=nullptr){
            if(less->has(obj)){
                return true;
            }
        }
        if(more!=nullptr){
            return more->has(obj);
        }
        return false;
    }
    vector<T> collapse(){
        vector<T> ret;
        if(less!=nullptr){
            vector<T> y = less->collapse();
            ret.insert(ret.end(), y.begin(), y.end());
        }
        ret.push_back(val);
        if(more!=nullptr){
            vector<T> y = more->collapse();
            ret.insert(ret.end(), y.begin(), y.end());
        }
        return ret;
    }
    size_t height(){
        size_t lmax = 0;
        size_t mmax = 0;
        if(less!=nullptr){
            lmax = less->height();
        }
        if(more!=nullptr){
            mmax = more->height();
        }
        return ((lmax < mmax)?mmax:lmax) + 1;
    }
    vector<vector<char> > toChars(int height){
        vector<vector<char> > ret;
        vector<char> line;
        for(int y = 0; y < height; y++){
            line.clear();
            for(int x = 0; x < pow(2,height) - 1; x++){
                line.push_back(' ');
            }
            ret.push_back(line);
        }
        ret.at(0).at((pow(2,height) / 2)-1) = to_string(val)[0];
        vector<vector<char> > l;
        vector<vector<char> > m;
        if(less!=nullptr){
            l = less->toChars(height-1);
            for(int y = 1; y < height; y++){
                for(int x = 0; x < pow(2,height-1)-1; x++){
                    ret.at(y).at(x) = l.at(y-1).at(x);
                }
            }
        }
        if(more!=nullptr){
            m = more->toChars(height-1);
            for(int y = 1; y < height; y++){
                for(int x = 0; x < pow(2,height-1)-1; x++){
                    ret.at(y).at((pow(2,height)/2) + x) = m.at(y-1).at(x);
                }
            }
        }
        return ret;
    }
};

template<typename T>
treeNode<T> * genTree(vector<T> elems){
    if(elems.size() == 0){
        return nullptr;
    }
    if(elems.size() == 1){
        return new treeNode<T>(elems.at(0));
    }
    size_t mid = elems.size()/2;
    treeNode<T> * ret = new treeNode<T>(elems.at(mid));
    vector<T> less;
    for(int i = 0; i < mid; i++){
        less.push_back(elems.at(i));
    }
    vector<T> more;
    for(int i = mid + 1; i < elems.size(); i++){
        more.push_back(elems.at(i));
    }
    ret->less = genTree<T>(less);
    ret->more = genTree<T>(more);
    return ret;
}

template <typename T>
struct binaryTree{
    treeNode<T> * root;
    size_t size;
    binaryTree(T val){
        root = new treeNode<T>(val);
        size = 1;
    }
    binaryTree(vector<T> elems){
        root = genTree<T>(elems);
        size = elems.size();
    }
    binaryTree(){
        root = nullptr;
        size = 0;
    }
    ~binaryTree(){
        if(root!=nullptr){
            delete root;
        }
    }
    void push(T obj){
        if(root==nullptr){
            size++;
            root = new treeNode<T>(obj);
            return;
        }
        if(root->attach(obj)){
            size++;
        }
    }
    bool has(T obj){
        if(root==nullptr){
            return false;
        }
        return root->has(obj);
    }
    vector<T> collapse(){
        if(root==nullptr){
            return vector<T>();
        }
        return root->collapse();
    }
    void resize(){
        if(size==0){return;}
        treeNode<T> * oldR = root;
        root = genTree<T>(collapse());
        delete oldR;
    }
    size_t height(){
        return root->height();
    }
    string toString(){
        return toString(root->toChars(root->height()));
    }
};

#endif /* BINARYTREE_H */


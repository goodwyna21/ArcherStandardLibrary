#ifndef COORDGEOMETRY_H
#define COORDGEOMETRY_H

#include <vector>
#include <cmath>
#include <initializer_list>
using namespace std;
#define uint unsigned int

struct Vec{ //Mathematical vector
    uint Dimension;
    vector<double> coords;
    
    //initializers
    void _defaultInitialize(const uint d){
        Dimension = d;
        coords = vector<double>(Dimension,0);
    }
    void _arrayInitialize(const uint d, const double vals[]){
        _defaultInitialize(d);
        for(uint i = 0; i < Dimension; i++){
            coords.at(i)=(vals[i]);
        }
        delete vals;
    }
    
    void _checkDim(Vec& v){
        if(v.Dimension!=Dimension){
            throw logic_error("Error: Invalid operation between a Vec of dimension " 
                  + to_string(Dimension)+" and Vec of dimension "+to_string(v.Dimension));} }

    //constructors
    Vec(const uint d=0){
        _defaultInitialize(d);
    }
    Vec(uint d, double vals[]){
        _arrayInitialize(d,vals);
    }
    Vec(const initializer_list<double>& vals){ //inline array initialization
        size_t d = vals.size();
        double arr[d];
        uint i = 0;
        for(double n : vals){
            arr[i]=n;
            i++;
        }
        _arrayInitialize(d,arr);
    }
    Vec(const vector<double>& vals){
        _arrayInitialize(vals.size(),&vals[0]);
    }
    Vec(Vec& v){(*this)=(v);}
    
    //methods
    Vec * clonePntr(){
        return new Vec(coords);
    }
    Vec clone(){
        Vec * ptr = clonePntr();
        Vec ret = *ptr;
        delete ptr;
        return ret;
    }
    
    operator vector<double>() {
        return coords;
    }
    
    //maths
    double& operator[] (const uint n){
        return coords.at(n);
    }
    Vec& operator+= (Vec v){ //vector addition
        _checkDim(v);
        for(uint i = 0; i < Dimension; i++){
            coords[i] += v[i];
        }
        return *this;
    }
    Vec operator+ (Vec v){
        Vec ret;
        ret = clone();
        ret+=v;
        return ret;
    }
    Vec& operator-= (Vec v){
        (*this) += (v*-1);
        return *this;
    }
    Vec operator- (Vec v){
        Vec ret = clone();
        ret-=v;
        return ret;
    }
    Vec& operator*= (double n){ //scalar multiplication
        for(uint i = 0; i < Dimension; i++){
            coords.at(i)*=n;
        }
        return *this;
    }
    Vec operator* (double n){
        Vec ret = clone();
        ret*=n;
        return ret;
    }
    double dot(Vec v){
        _checkDim(v);
        double sum = 0;
        for(uint i = 0; i < Dimension; i++){
            sum+=coords.at(i)*v[i];
        }
        return sum;
    }        
    //geometry
    double distSquared(Vec& v){
        _checkDim(v);
        uint sum=0;
        for(uint i = 0; i < Dimension; i++){
            sum+= pow(coords.at(i) - v[i],2);
        }
        return sum;
    }
    double dist(Vec& v){
        return sqrt(distSquared(v));
    }
    double normSquared(){
        double sum=0;
        for(uint i = 0; i < Dimension; i++){
            sum+= coords.at(i)*coords.at(i);
        }
        return sum;
    }
    double norm(){ 
        // ||v||
        // length of the vector
        return sqrt(normSquared());
    }
    double angleTo(Vec& v){
        return acos(dot(v) / (norm() * v.norm()));
    }
    
    string toString(string space=""){
        string ret = space+"\u3008";
        for(int i = 0; i < Dimension; i++){
            ret+=to_string(coords.at(i));
            if(i+1 < Dimension){
                ret += ",";
            }
        }
        return ret + "\u3009";
    }
};
Vec operator* (double n, Vec& v){
    return v*n;
}

struct coordPlane{
    Vec j;
    Vec k;
    Vec origin;
    string sym;
    
    coordPlane(string s=""){
        j=Vec(3);
        k=Vec(3);
        origin=Vec(3);
        sym=s;
    }
    
    coordPlane(Vec O, Vec Ĵ, Vec K, string s=""){
        Ĵ._checkDim(K);
        O._checkDim(Ĵ);
        if(O.Dimension!=3){
            throw logic_error("Error: cannot initialize 2d coordinate plane with Vec of dimension " 
                  + to_string(O.Dimension));}
        origin=O;
        j = Ĵ;
        j = K;
        sym=s;
    }

    void _checkTwoD(Vec v){
        if(v.Dimension!=2){
            throw logic_error("Error: Invalid operation between a Vec of dimension " 
                  + to_string(v.Dimension)+" and 2d coordinate plane.");} }
    
    Vec toRealSpace(Vec v){
        _checkTwoD(v);
        return ((j*v[0])+(k*v[1])+origin);
    }
    
    Vec operator() (double x, double y){
        return toRealSpace(Vec({x,y}));
    }
};

#endif /* COORDGEOMETRY_H */


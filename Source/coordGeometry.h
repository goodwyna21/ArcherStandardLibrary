#ifndef COORDGEOMETRY_H
#define COORDGEOMETRY_H

#include <vector>
#include <cmath>
#include <initializer_list>
using namespace std;

/*
Provides 'Vec' (vector) and 'coordPlane' classes for use in
coordinate geometry.
 */

#define uint unsigned int
const string LEFTVECBRACE = "\u27E8";
const string RIGHTVECBRACE= "\u27E9";

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
    }
    
    void _checkDim(Vec v){
        if(v.Dimension!=Dimension){
            throw logic_error("Error: Invalid operation between a Vec of dimension " 
                  + to_string(Dimension)+" and Vec of dimension "+to_string(v.Dimension));} }
    ~Vec(){}
    Vec(){}
    //constructors
    Vec(uint d, double vals[]){
        _arrayInitialize(d,vals);
    }
    Vec(initializer_list<double> vals){ //inline array initialization
        vector<double> v(vals.begin(),vals.end());
        _arrayInitialize(v.size(),&v[0]);
    }
    Vec(vector<double> vals){
        _arrayInitialize(vals.size(),&vals[0]);
    }
    Vec(Vec& v){(*this)=(v);}
    Vec(Vec a, Vec b){(*this)=(b-a);}
    
    Vec(double a, double b){
        double arr[] = {a,b};
        _arrayInitialize(2,arr);
    }
    Vec(double a, double b, double c){
        double arr[] = {a,b,c};
        _arrayInitialize(3,arr);
    }
    
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
    Vec& normalize(){
        double len = norm();
        for(int i = 0; i < Dimension; i++){
            coords[i] /= len;
        }
        return *this;
    }
    //maths
    double& operator[] (const uint n){
        return coords.at(n);
    }
    Vec& setNorm(double n){
        double len = norm();
        for(uint i = 0; i < Dimension; i++){
            coords[i] *= (n/len);
        }
        return *this;
    }
    Vec& stretch(double n){return setNorm(n);}
    
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
    Vec& operator/= (double n){ //scalar division
        for(uint i = 0; i < Dimension; i++){
            coords.at(i)/=n;
        }
        return *this;
    }
    Vec operator/ (double n){
        Vec ret = clone();
        ret/=n;
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
    Vec cross(Vec v){
        _checkDim(v);
        return {
            (coords.at(2) * v[3]) - (coords.at(3) * v[2]),
            (coords.at(3) * v[1]) - (coords.at(1) * v[3]),
            (coords.at(1) * v[2]) - (coords.at(2) * v[1])
        };
    }
    //geometry
    double distSquared(Vec& v){
        return ((*this)-v).normSquared();
    }
    double dist(Vec& v){
        return ((*this)-v).norm();
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
    
    string toString(string tag=""){
        string ret = tag+LEFTVECBRACE;
        string s;
        for(int i = 0; i < Dimension; i++){
            s=to_string(((int)(coords.at(i)*100)));
            s.insert(s.end()-2,'.');
            ret+=s;
            if(i+1 < Dimension){
                ret += ",";
            }
        }
        return ret + RIGHTVECBRACE;
    }
};
Vec operator* (double n, Vec v){
    return v*n;
}
double dot(Vec a, Vec b){
    a._checkDim(b);
    double sum = 0;
    for(uint i = 0; i < a.Dimension; i++){
        sum+=a.coords.at(i)*b[i];
    }
    return sum;
}
Vec cross(Vec a, Vec b){
    a._checkDim(b);
    return {
        (a[2] * b[3]) - (a[3] * b[2]),
        (a[3] * b[1]) - (a[1] * b[3]),
        (a[1] * b[2]) - (a[2] * b[1])
    };
}

struct coordPlane{
    Vec j;
    Vec k;
    Vec origin;
    string sym;
    
    coordPlane(string s=""){
        j=Vec({0,0,0});
        k=Vec({0,0,0});
        origin=Vec({0,0,0});
        sym=s;
    }
    
    coordPlane(Vec O, Vec Ĵ, Vec K, string s=""){
        if(O.Dimension!=3 || 
           Ĵ.Dimension!=3 ||
           K.Dimension!=3){
            throw logic_error("Error: cannot initialize 2d coordinate plane with Vec of dimension " 
                  + to_string(O.Dimension));}
        origin=O;
        j = Ĵ;
        k = K;
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
    Vec operator() (Vec v){
        return toRealSpace(v);
    }
    Vec operator() (double x, double y){
        return toRealSpace(Vec({x,y}));
    }
};

#endif /* COORDGEOMETRY_H */


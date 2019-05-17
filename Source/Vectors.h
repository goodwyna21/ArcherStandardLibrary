#ifndef VECTORS_H
#define VECTORS_H

#include <vector>
#include <cmath>
using namespace std;

template <typename T>
size_t find(vector<T> vec, T elem){
    typename vector<T>::iterator it = find(vec.begin(),vec.end(),elem);
    if (it!=vec.end()){return distance(vec.begin(),it);}
    else{return string::npos;}
}

/*
 * Math functions
 */
double sum(vector<double> v){
    double tot=0; for(int i=0;i<v.size();i++){tot+=v.at(i);}return tot;}
int sum(vector<int> v){
    int tot=0; for(int i=0;i<v.size();i++){tot+=v.at(i);}return tot;}
size_t sum(vector<size_t> v){
    size_t tot=0; for(int i=0;i<v.size();i++){tot+=v.at(i);}return tot;}

/*
 * Vector string functions
 * most of these convert a type of vector to a string or vector of strings
 */
string toString(vector<string> vec,string sep="\n"){
    string ret = "";
    for(int i = 0; i < vec.size();i++){
        ret+=vec.at(i);
        if(i+1 < vec.size()){ret+=sep;}
    }
    return ret;
}
vector<string> charToStrVec(vector<char> vec){
    vector<string> ret;
    for(int i = 0; i < vec.size(); i++){ret.push_back(string(1,vec.at(i)));}
    return ret;
}
string toString(vector<vector<char> > vec,string sep=""){
    string ret = "";
    for(int y = 0; y < vec.size(); y++){
        ret += toString(charToStrVec(vec.at(y)),sep) + "\n";
    }
    return ret;
}
string toString(vector<int> vec, string sep=", "){
    string ret = "";
    for(int i = 0; i < vec.size(); i++){
        ret += to_string(vec.at(i));
        if(i+1<vec.size()){
            ret+=sep;
        }
    }
    return ret;
}
//these take a vector of numbers and return a vector of strings
vector<string> toVecOfStr(vector<double> n){
    vector<string> ret;for(int i=0;i<n.size();i++){ret.push_back(to_string(n.at(i)));}return ret;}
vector<string> toVecOfStr(vector<int> n){
    vector<string> ret;for(int i=0;i<n.size();i++){ret.push_back(to_string(n.at(i)));}return ret;}
vector<string> toVecOfStr(vector<size_t> n){
    vector<string> ret;
    for(int i=0;i<n.size();i++){
        ret.push_back(to_string(n.at(i)));
    }
    return ret;}

//sorts a vector of strings
bool strCompare (string a, string b) {return a<b;} 
void sortVec(vector<string>& v){
    sort(v.begin(),v.end(),strCompare);
}

#endif /* VECTORS_H */


#ifndef BODIES_H
#define BODIES_H

#include "Constants.h"

struct Color{
    uint r,g,b;
    Color(uint R=255,uint G=255, uint B=255){
        r=(R>255)?255:R;
        g=(G>255)?255:G;
        b=(B>255)?255:B;
    }
    Color(initializer_list<uint>& vals){
        vector<uint> v = vals;
        r = (v[0]>255)?255:v[0];
        g = (v[1]>255)?255:v[1];
        b = (v[2]>255)?255:v[2];
    }
    uint& operator[] (uint n){
        return (n==0)?r:((n==1)?g:b);}
    
    static Color gradient(double val, double low, double high, Color a, Color b){
        double p = compress(val,low,high,0,1);
        return {(uint)(a.r + p * (b.r - a.r)),
                (uint)(a.g + p * (b.g - a.g)),
                (uint)(a.b + p * (b.b - a.b))};}
    static Color blend(Color a, Color b){
        return Color::gradient(0.5,0,1,a,b);
    }
};

struct Lamp{
    Vec pos;
    Color color;
    Lamp(){pos={0,0,0};color={255,255,255};}
    Lamp(Vec& p, Color c={255,255,255}){
        pos = p;
        color=c;
    }
};

struct Body{
    Vec center;
    Color color;
    Body(){
        center={0,0,0};
        color={255,0,0};
    }
    virtual ~Body(){}
    virtual string type(){
        return "Body";
    }
    virtual double distSquared(Vec v){
        bp("distSquared not defined");
        throw runtime_error("Distance squared function not defined");
    }
    virtual double dist(Vec v){
        bp("dist not defined");
        throw runtime_error("Distance function not defined");
    }
};

struct Sphere : virtual Body{
    double radius;
    Sphere(){
        center={0,0,0};
        color={255,0,0};
        radius=25;
    }
    Sphere(Vec cent, double r, Color c={255,0,0}){
        center = cent;
        color = c;
        radius = r;
    }
    ~Sphere(){}
    string type(){
        return "Sphere";
    }
    double dist(Vec v){
        return center.dist(v) - radius;
    }
    double distSquared(Vec v){
        return pow(dist(v),2);
    }
};

struct Segment : Body{
    Vec p1;
    Vec p2;
    Segment(){}
    ~Segment(){}
    string type(){
        return "Segment";
    }
    Segment(Vec P1, Vec P2, Color c={255,0,0}){
        center = {P1[x] + (P2[x]-P1[x])/2,
                  P1[y] + (P2[y]-P1[y])/2,
                  P1[z] + (P2[z]-P1[z])/2};
        color = c;
        p1=P1;
        p2=P2;
    }
    double getT(Vec p){
        return 0.5 + ((pow(p1.dist(p),2)-pow(p2.dist(p),2))/(2*pow(p1.dist(p2),2)));
    }
    Vec closestPnt(Vec p){
        double t = getT(p);
        if(t > 1){
            return p2;
        }else if(t < 0){
            return p1;
        }else{
            return {p1[x] + t*(p2[x] - p1[x]),
                    p1[y] + t*(p2[y] - p1[y]),
                    p1[z] + t*(p2[z] - p1[z])};
        }
    }
    double dist(Vec p){
        return closestPnt(p).dist(p);}
    double distSquared(Vec p){
        return closestPnt(p).distSquared(p);}
};

struct Cylinder : Segment{
    double radius;
    string type(){
        return "Cylinder";
    }
    Cylinder(Vec P1, Vec P2, double r, Color c={255,0,0}) 
            : Segment(P1,P2,c){
        radius = r;
    }
    double dist(Vec p){
        return Segment::dist(p) - radius;
    }
    double distSquared(Vec p){
        return pow(dist(p),2);
    }
};

#endif /* BODIES_H */


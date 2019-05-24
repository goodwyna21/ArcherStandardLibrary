#ifndef CAMERA_H
#define CAMERA_H

#include "Image.h"

struct _marchWrapper{
    double dist;
    Body * obj;
    Vec pnt;
    string toString(){
        return to_string(dist) + " " + ((obj==nullptr)?"nullptr":obj->type()) + " " + pnt.toString();
    }
};

struct Ray{
    Vec origin, target, unit, pos;
    Scene * scene;
    
    Ray(Vec pnt, Vec targ, Scene * s){
        origin = pnt;
        pos = origin;
        target = targ;
        unit = (target-origin);
        unit /= unit.norm();
        scene = s;
    }
    
    _marchWrapper send(){
        _distWrapper close = scene->minDist(pos);
        if(close.obj==nullptr){return {0,nullptr,pos};}
        while(close.dist > MARCHTHRESH){
            pos+=(close.dist*unit);
            close = scene->minDist(pos);
            if(!scene->inbounds(pos)){
                return {0,nullptr,pos};
            }
        }
        return {close.dist,close.obj,pos};
    }
};

struct Camera{
    Scene * scene;
    Vec pos,target,scrCent;
    coordPlane screen;
    double fovX,fovY;
    double scrW,scrH;
    Camera(){}
    Camera(Vec pnt,Vec targ,double FOVX,double FOVY, Scene * s){
        pos=pnt;
        target=targ;
        fovX=FOVX;
        fovY=FOVY;
        scene = s;
        
        Vec toTarg = (target - pos);
        scrCent = (pos + toTarg.stretch(SCRDIST));
        
        scrW = SCRDIST*sin(fovX);
        scrH = SCRDIST*sin(fovY);
        
        _calcScreen();
    }
    void _calcScreen(){
        double dx = scrCent[x] - target[x];
        double dy = scrCent[y] - target[y];
        double dz = scrCent[z] - target[z];
        double m = ((dz==0)?0:(-1*dx/dz));
        double d = sqrt(pow(dx,2)+pow(dz,2));
        double n = ((dy==0)?0:(-1*d/dy));
        coordPlane gamma(target,(1.0/d)*Vec({dx,0,dz}),{0,1,0},"\u03B3");
        Vec j = (1.0/sqrt(1+pow(m,2)))*Vec({-m,0,1});
        Vec k = (-1.0/sqrt(1+pow(n,2)))*gamma({n,1});
        screen = coordPlane(
            scrCent, //omega
                j,k,
            "\u1E9F");
    }
    
    Color _genColor(_marchWrapper& walk){
        if(walk.obj==nullptr){return scene->background;}
        if(inShadow(walk.pnt)){return {0,0,0};}
        return walk.obj->color;
    }
    
    //Coloring Methods:
    Color fill(_marchWrapper& walk){return walk.obj->color;}
    Color distance(_marchWrapper& walk){
        return Color::gradient(walk.pnt.dist(pos),50,150,walk.obj->color,scene->diffuse);
    }
    Color srcGrad(_marchWrapper& walk){
        Vec toPnt(pos,walk.pnt);
        Vec toCent(pos,walk.obj->center);
        
        return Color::gradient(toPnt.angleTo(toCent),0,pi/2,walk.obj->color,scene->diffuse);
    }
    Color flood(_marchWrapper& walk){
        return Color(0,0,0);
    }
    Color lightGradient(_marchWrapper& walk){
        Vec cent(scene->source.pos,walk.obj->center);
        cent/=cent.norm();
        Vec inter(scene->source.pos,walk.pnt);
        inter/=inter.norm();
        return Color::gradient(Vec(cent,inter).norm(),0,1,walk.obj->color,{0,0,0});
    }
    bool inShadow(Vec p){
        Vec v(p,scene->source.pos);
        v/=v.norm();
        Segment line((v*MARCHTHRESH)+p,scene->source.pos);
        for(int i = 0; i < scene->objects.size(); i++){
            if(scene->objects.at(i)->dist(line.closestPnt(scene->objects.at(i)->center)) <= 0){
                return true;
            }
        }
        return false;
    }

    
    Image render(double width,double height){
        Image img(width,height);
        _marchWrapper walk;
        for(uint ypx = 0; ypx < height; ypx++){
            for(uint xpx = 0; xpx < width; xpx++){
                walk = Ray(pos,
                    screen({compress(xpx,0,width-1,-1*scrW,scrW),
                            compress(ypx,0,height-1,scrH,-1*scrH)}),
                    scene
                ).send();
                img(xpx,ypx)=_genColor(walk);
            }
        }
        return img;
    }
};

#endif /* CAMERA_H */


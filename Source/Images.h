#ifndef IMAGES_H
#define IMAGES_H

#include "DataStructures.h"
#include "Maths.h"
#include <bitset>
#include <fstream>
#define byte unsigned char
using namespace std;

/*
Provides an Image struct which can be saved to a file.
Also contains a Color struct for handling RGB colors
 */

struct Color{
    int r,g,b;
    Color(uint R=255,uint G=255, uint B=255){
        r=(R>255)?255:R;
        g=(G>255)?255:G;
        b=(B>255)?255:B;
    }
    Color(initializer_list<int> vals){
        vector<int> v = vals;
        r = (v[0]>255)?255:v[0];
        g = (v[1]>255)?255:v[1];
        b = (v[2]>255)?255:v[2];
    }
    int& operator[] (uint n){
        return (n==0)?r:((n==1)?g:b);}
    string toString(){
        return "(" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ")";
    }
    static Color gradient(double val, double low, double high, Color a, Color b){
        double p = compress(val,low,high,0,1);
        return {(int)(a.r + (p * (b.r - a.r))),
                (int)(a.g + (p * (b.g - a.g))),
                (int)(a.b + (p * (b.b - a.b)))};}
    static Color blend(Color a, Color b){
        return Color::gradient(0.5,0,1,a,b);
    }
};

vector<byte> intToBytes(int paramInt)
{
    vector<byte> vec(4);
    int i = 32; while ( i != 0 ) { 
        vec[i/8] = paramInt >> i; 
        i -= 8; 
    }
    return vec;
}

struct Image{
    uint width, height;
    vector<vector<Color> > pixels;
    Image(){}
    Image(uint Width, uint Height){
        width = Width;
        height= Height;
        pixels = vector<vector<Color> >(width,vector<Color>(height,{255,255,255}));
    }
    Color& operator() (uint x, uint y){
        return pixels[x][y];
    }
    
    void savePPM(string fname){
        ofstream out(fname.c_str(),ios::out);
        out << "P3" << endl;
        out << width << " " << height << endl;
        out << "255" << endl;
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                out << pixels[x][y].r << " ";
                out << pixels[x][y].g << " ";
                out << pixels[x][y].b << "\n";
            }
        }
        out.close();
    }
};

#endif /* IMAGES_H */


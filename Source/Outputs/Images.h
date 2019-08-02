#ifndef IMAGES_H
#define IMAGES_H

//includes
#include "Debugging.h"
using namespace std;

double _compress(double val, double inMin, double inMax, double outMin, double outMax){
 return (((val - inMin)/(inMax-inMin)) * (outMax-outMin)) + outMin;}

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
        double p = _compress(val,low,high,0,1);
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
    void set(uint x, uint y, Color c){
        if(x >= 0 && x < width && y >= 0 && y < height){
            pixels[x][y] = c;
        }
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


    void line(uint x1, uint y1, uint x2, uint y2, Color c={0,0,0},uint stroke=1){
        if(x1 > x2){ //swap
            uint tx = x1;
            uint ty = y1;
            x1 = x2;
            y1 = y2;
            x2 = tx;
            y2 = tx;
        }
        int dx = x2 - x1;
        int dy = y2 - y1;
        if(dx == 0){
            for(int y = ((y1<y2)?y1:y2); y < ((y1<y2)?y2:y1); y++){
                for(int x = -0.5*stroke; x <= 0.5*stroke; x++){
                    set(x1+x,y,c);
                }
            }
        }
        double m = (1.0*dy)/dx;
        int y;
        for(int x = x1; x < x2; x++){
            y = (m*(x-x1))+y1;
            rect(x-stroke,y-stroke,x+stroke,y+stroke,c);
        }
    }
    void rect(uint x1, uint y1, uint x2, uint y2, Color c={0,0,0}){
        if(x1 > x2){
            uint tm = x1;
            x1 = x2;
            x2 = tm;
        }
        if(y1 > y2){
            uint tn = y1;
            y1 = y2;
            y2 = tn;
        }
        for(int x = x1; x < x2; x++){
            for(int y = y1; y < y2; y++){
                pixels[x][y] = c;
            }
        }
    }
    void circle(uint x1, uint y1, uint radius, Color c={0,0,0}){
        for(int x = (x1 - radius); x < x1 + radius; x++){
            pixels[x][y1] = {255,0,0};
            for(int y = y1 - sqrt((radius*radius) - ((x-x1)*(x-x1))); y < y1 + sqrt((radius*radius) - ((x-x1)*(x-x1))); y++){
                pixels[x][y] = c;
            }
        }
    }
    void text(string s, uint x1, uint y1, Color c={0,0,0}, uint size=1){
        string pix;
        for(int i = 0; i < s.size(); i++){
            if(s[i] >= 97 && s[i] <= 122){ //lowercase to uppercase
                s[i]-=32;
            }
            pix = GLYPHS[GLYPHLIST.find(s[i])];
            for(int x = 0; x < GLYPHWIDTH; x++){
                for(int y = 0; y < GLYPHHEIGHT; y++){
                    if(pix[(GLYPHWIDTH*y) + x] == GLYPHSETPX){
                        rect(x1 + (i*size*(GLYPHWIDTH+1)) + x*size, y1 + y*size,x1 + (i*size*(GLYPHWIDTH+1)) + x*size + size, y1 + y*size + size, c);
                    }
                }
            }
        }
    }
};

#endif /* IMAGES_H */

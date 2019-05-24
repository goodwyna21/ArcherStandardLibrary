#ifndef IMAGE_H
#define IMAGE_H

#include "Scene.h"
#include <bitset>

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
    vector<vector<Color> > pixels;
    uint width,height;
    Image(uint Width, uint Height){
        width = Width;
        height=Height;
        pixels=vector<vector<Color> >(height,vector<Color>(width,{255,255,255}));
    }
    Color& operator() (uint x, uint y){
        return pixels.at(y).at(x);
    }
    
    void saveBinary(string fname){
        uint dataSize = 8+(3*width*height);
        char vdata[dataSize];
        for(int i = 24; i >= 0; i-=8) { 
            vdata[i/8] = (width >> i); 
            vdata[4+(i/8)] = (height >> i); 
        }
        int i = 0;
        for(int Y = 0; Y < height; Y++){
            for(int X = 0; X < width; X++){
                vdata[8+i]=pixels.at(Y).at(X).r;
                vdata[9+i]=pixels.at(Y).at(X).g;
                vdata[10+i]=pixels.at(Y).at(X).b;
                i+=3;
            }
        }
        fstream out;
        out.open(fname.c_str(),ios::out | ios::binary);
        for(i = 0; i < dataSize; i++){
            cout << pad(to_string(i).c_str(),3,' ',"right") << ") 0x";
            cout << bitset<8>((int)vdata[i]).to_string() << ' ' << (int)(byte)vdata[i] << "\n";
        }
        out.write(vdata,(8+(3*width*height)));
        out.close();
        return;
    }
    
    void savePthree(ostream& out, string fname){
        out << "P3" << endl;
        out << width << " " << height << endl;
        out << "255" << endl;
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                out << pixels.at(y).at(x).r << " ";
                out << pixels.at(y).at(x).g << " ";
                out << pixels.at(y).at(x).b << endl;
            }
        }
    }
};

#endif /* IMAGE_H */


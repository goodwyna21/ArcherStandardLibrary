#include "Camera.h"

int main(int argc, char** argv) {
    cout << "start\n";
    
    Vec cam({0,0,-200});
    Vec targ = {0,0,0};
    double fov = pi/4;
    vector<Body *> bulbs = {
        new Sphere({ 0, 0, 0},25,{255,255,255}),//center white
        new Sphere({ 100,0,0},25,{255,0,0}),    //pos x  red
        new Sphere({-100,0,0},25,{255,255,0}),  //neg x  yellow
        new Sphere({0, 100,0},25,{0,255,0}),    //pos y  green
        new Sphere({0,-100,0},25,{0,255,255}),  //neg y  cyan
        new Sphere({0,0, 100},25,{0,0,255}),    //pos z  blue
        new Sphere({0,0,-100},25,{255,0,255}),  //neg z  purple
    };
    
    Scene * s = new Scene(400,400,400,{0,0,255});
    s->objects = bulbs;
    
    Camera c;
    c = Camera(cam,targ,fov,fov,s);
    s->source = Lamp(cam);
    Image img = c.render(100,100);
    string fname = "/Users/goodwyna21/Desktop/newRenderTest.ppm";
    
    //img.saveBinary(fname);
    
    ofstream out(fname.c_str(),ios::out);
    img.savePthree(out, fname);
    out.close();
    /*string comm = "open " + fname;
    system(comm.c_str());
    img.saveBinary(fname);*/
    delete s;
    return 0;
}


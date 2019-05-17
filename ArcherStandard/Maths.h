#ifndef MATHS_H
#define MATHS_H

using namespace std;

double compress(double val, double inMin, double inMax, double outMin, double outMax){
    return (((val - inMin)/(inMax-inMin)) * (outMax-outMin)) + outMin;}

#endif /* MATHS_H */


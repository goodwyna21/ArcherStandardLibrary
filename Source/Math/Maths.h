#ifndef MATHS_H
#define MATHS_H

/*
Provides generic math functions
 */
#include "_Header.h"
using namespace std;

double compress(double val, double inMin, double inMax, double outMin, double outMax){
    return (((val - inMin)/(inMax-inMin)) * (outMax-outMin)) + outMin;}
#endif /* MATHS_H */

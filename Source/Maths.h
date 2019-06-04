#ifndef MATHS_H
#define MATHS_H

#include <iterator>
using namespace std;

/*
Provides generic math functions
 */

double compress(double val, double inMin, double inMax, double outMin, double outMax){
    return (((val - inMin)/(inMax-inMin)) * (outMax-outMin)) + outMin;}
#endif /* MATHS_H */


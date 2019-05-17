#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
using namespace std;
/*
 * Breakpoints for debugging
 */
int BKPCNT=1;
void bp(string msg=""){           
    cout << "\n------------\nBreakpoint " << BKPCNT << ((msg.size()==0?"":"\n"+msg)) << "\n------------\n";
    cin.get();
    BKPCNT++;}
void bp(const char* msg){bp(string(msg));}
void bp(bool b){bp(b?"true":"false");}
void bp(int n){bp(to_string(n));}
void bp(double n){bp(to_string(n));}
void bp(char c){bp(string(1,c));}
void bp(size_t n){bp((int)n);}

#endif /* DEBUGGING_H */


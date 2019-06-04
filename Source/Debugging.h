#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
using namespace std;
/*
Provides breakpoint functions, useful for finding errors in code.
A breakpoint clearly outputs a message or variable if supplied,
then waits for the user to press enter. In my experience these
are more convenient and more effective than simply
'cout<<"Here\n"' because many times segmentation
faults can occur 'out-of-order' and can fail at
unpredictable points during execution, but waiting for input
seems to eliminate this problem, allowing you to easily find the
portion of code responsible. Each time a breakpoint is called it
increments a counter, so you can follow execution even without
providing a message.
 */

struct bkpnts{
    static unsigned int BKPCNT;
    ostream os;
    istream is;
    bkpnts(ostream& out=cout,istream& in=cin) : os(out.rdbuf()), is(in.rdbuf()) {}
    ~bkpnts(){}
    string operator() (string msg=""){
        os << "\n------------\nBreakpoint " << BKPCNT << ((msg.size()==0?"":"\n"+msg)) << "\n------------\n";
        BKPCNT++;
        return to_string(is.get());
    }
    string operator() (const char* msg){return (*this)(string(msg));}
    string operator() (bool b){return (*this)(b?"true":"false");}
    string operator() (int n){return (*this)(to_string(n));}
    string operator() (double n){return (*this)(to_string(n));}
    string operator() (char c){return (*this)(string(1,c));}
    string operator() (size_t n){return (*this)((int)n);}
    string operator() (unsigned int n){return (*this)((int)n);}
};
unsigned int bkpnts::BKPCNT = 1;
bkpnts bp;

#endif /* DEBUGGING_H */


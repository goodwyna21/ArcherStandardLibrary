#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
using namespace std;
/*
 * Breakpoints for debugging
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


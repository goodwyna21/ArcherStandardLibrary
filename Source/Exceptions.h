#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <termios.h>
#include <sstream>
using namespace std;

/*
Provides a compact class for throwing custom runtime errors.
*/

//Use like: throw runtime_error(ErrForm() << "oopsie " << var >> ErrForm::to_str);
struct ErrForm{
    stringstream stream_;
    ErrForm() {}
    ~ErrForm() {}
    template <typename Type>
    ErrForm & operator << (const Type & value){
        stream_ << value;
        return *this;}
    string str() const {return stream_.str();}
    operator string () const {return stream_.str();}
    enum ConvertToString {to_str};
    string operator >> (ConvertToString) { return stream_.str(); }
    ErrForm(const ErrForm &);
    ErrForm & operator = (ErrForm &);
};

#endif /* EXCEPTIONS_H */


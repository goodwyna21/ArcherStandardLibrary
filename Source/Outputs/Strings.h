#ifndef STRINGS_H
#define STRINGS_H

/*
Provides generic functions for handling strings and converting
other types to strings.
Also contains the mlstring (multi-line string) struct, which is
used for operating on large strings.
*/
#include "Images.h"
using namespace std;

/*
 * ANSI escape codes
 */
const string ANSIESC = "\33[";
const string DEFALT = ANSIESC+"0m";
const string FXUNDR = ANSIESC+"4m";
const string NOUNDR = ANSIESC+"24m";
enum ansiColor{BLACK,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE,DEFAULT};
const ansiColor PURPLE=MAGENTA;
const string ANSITXT[9]={ANSIESC+"30m",ANSIESC+"31m",ANSIESC+"32m",ANSIESC+"33m",ANSIESC+"34m",ANSIESC+"35m",ANSIESC+"36m",ANSIESC+"37m",ANSIESC+"39m"};
const string ANSIBKG[9]={ANSIESC+"40m",ANSIESC+"41m",ANSIESC+"42m",ANSIESC+"43m",ANSIESC+"44m",ANSIESC+"45m",ANSIESC+"46m",ANSIESC+"47m",ANSIESC+"49m"};
/*
 * These are generic string functions,
 * they're here because mlstring needs them
 */
size_t psize(string s){ //number of printable characters in string
    size_t tot=0;
    for(int i = 0; i < s.size(); i++){
        if(s[i]!='\n')tot++;
    }
    size_t n=0,m=0;
    while((n=s.find(ANSIESC,n))!=string::npos){
        m=s.find('m',n);
        if(m==string::npos)break;
        tot-=m-(n-1);
        n=m;
    }

    return tot;
}

string pad(string &s, int width,char fill=' ',string align="left"){
    while(psize(s)<width){
        if(align[0]=='l'||align[0]=='L'){
            s+=fill;
        }else{
            s.insert(s.begin(),1,fill);
        }
    }
    return s;
}
string pad(const char* c, int w,char f=' ',string a="left"){
    string s(c);
    return pad(s,w,f,a);
}

/*
 * multi-line string type
 */
struct mlstring{
    vector<string> lines;
    int pointer;
    size_t maxW;
    void init(string txt){
        pointer = -1;
        maxW=0;
        (*this)+=txt;
    }
    mlstring(string txt=""){
        init(txt);
    }
    operator string() {
      return this->toString();
    }
    string& at(size_t pos){
        return lines.at(pos);
    }
    string& operator[](size_t pos){
            return lines.at(pos);
    }
    mlstring& operator+=(string txt){
        string line="";
        bool toggle=false;
        for(int i = 0; i < txt.size(); i++){
            if(txt[i]!='\n'){
                line+=txt[i];
            }else{
                if(toggle){
                    lines.push_back(line);
                }else{
                    lines.at(lines.size()-1)+=line;
                }
                line="";
            }
        }
        return *this;
    }
    mlstring& operator+=(char c){
        if(c!='\n'){
            lines.at(lines.size()-1)+=c;
        }
        else{lines.push_back("");}
        return *this;
    }
    mlstring& operator=(mlstring const str){
        lines=str.lines;
        pointer=str.pointer;
        return *this;
    }
    mlstring& operator=(string const str){
        init(str);
        return *this;
    }

    size_t size(){
        return lines.size();
    }
    string toString(string sep="\n"){
        string ret="";
        for(int i = 0; i < lines.size(); i++){
            ret+=lines.at(i);
            if(i+1<lines.size()){ret+=sep;}
        }
        return ret;
    }
    size_t maxWidth(){
        maxW=0;
        for(int i = 0; i < lines.size(); i++){
            maxW=max(maxW,psize(lines.at(i)));
        }
        return maxW;
    }
    bool in(string& i){pointer++;if(pointer<lines.size()){i=lines.at(pointer);return true;}pointer=-1;return false;}
};

/*
 * String functions
 */
mlstring align(mlstring a,mlstring b, string sep="", string style="horizontal"){
    if(style[0]=='h'||style[0]=='H'){ //horizontal
        a.maxWidth();
        for(int i=0;i<b.lines.size();i++){
            if(i>=a.lines.size()){
                a.lines.push_back("");
            }
            a.lines.at(i)=pad(a.lines.at(i),a.maxW);
            a.lines.at(i)+=sep+b.lines.at(i);
        }
    }else{
        for(int i = 0; i < b.size(); i++){
            a.lines.push_back(b.lines.at(i));
        }
    }
    return a;
}

string setColor(string s,ansiColor c){
    return ANSITXT[c]+s+ANSITXT[DEFAULT];
}
string setHighlight(string s,ansiColor c){
    return ANSIBKG[c]+s+ANSIBKG[DEFAULT];
}
string toLower(string &s){
    for(int i = 0; i < s.size(); i++){
        if((int)s[i]>64&&(int)s[i]<91){
            s[i]=(char)(((int)s[i]) + 32);
        }
    }
    return s;
}
string toLower(const char* s){string str(s);return toLower(str);}

mlstring pad(mlstring &s, int width=-1,char fill=' ',string align="left"){
    if(width==-1){
        for(int i = 0; i < s.lines.size(); i++){
            width=max((int)s.lines.at(i).size(),width);
        }
    }
    for(int i = 0; i < s.lines.size(); i++){
        pad(s.lines.at(i),width,fill,align);
    }
    return s;
}
string addBorder(string s, string title=""){
    if(s[s.size()-1]=='\n'){s=s.substr(0,s.size()-1);}
    s="|"+s+"|";
    string hdr="+";
    if(title!=""){
        hdr+=string(psize(title),'-')+"+\n|"+title+"|\n|";}
    s=hdr+string(max(psize(s),(psize(title)))-2,'-') + "+\n"+s+"\n+" + string(psize(s)-2,'-') + "+\n";
    return s;
}
string addBorder(const char* c,string t=""){return addBorder(string(c),t);}
mlstring addBorder(mlstring s,string title=""){
    size_t maxW=0;
    for(int i = 0; i < s.lines.size(); i++){
        maxW=max(psize(s.lines.at(i)),maxW);
    }
    for(int i = 0; i < s.lines.size(); i++){
        s.lines.at(i)=pad(s.lines.at(i),maxW);
        s.lines.at(i).insert(s.lines.at(i).begin(),'|');
        s.lines.at(i)+="|";
    }
    s.lines.insert(s.lines.begin(),("+"+string(maxW,'-')+"+"));
    s.lines.push_back(("+"+string(maxW,'-')+"+"));
    if(title!=""){
        s.lines.insert(s.lines.begin(),"+"+string(psize(title),'-')+"+");
        s.lines.insert(s.lines.begin()+1,"|"+title+"|");
    }
    return s;
}

string niceDeci(double n){
    string tmp = to_string((int)(n*100));
    if(tmp!="0"){tmp.insert(tmp.end()-2,'.');}
    if(tmp.size() > 3){
        if(tmp.substr(tmp.size()-3)==".00"){tmp=tmp.substr(0,tmp.size()-3);}
        else if(tmp.substr(tmp.size()-3)==".99"){return niceDeci(n+((n<0?-1:1)*0.01));}
    }
    if(tmp[0]=='.'){tmp.insert(tmp.begin(),'0');}
    return tmp;
}



#endif /* STRING_H */

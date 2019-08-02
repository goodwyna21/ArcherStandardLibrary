#ifndef TABLE_H
#define TABLE_H

/*
Table.h provides a class for outputting data in a properly
formatted table, while abstracting away the string handling.
In addition, Tables can be used as menus from which a user can
select an item.
 */
#include "Strings.h"
using namespace std;

struct Table{
    vector<vector<string> > cells;
    string offhlight;
    string offtxt;
    string hlight;
    string txt;
    string title;
    string sep;
    string fill;
    string align;
    size_t beginX;
    size_t beginY;
    size_t rows;
    size_t cols;
    size_t dispWidth;
    size_t dispHeight;
    void init(string name="",size_t width=0,size_t height=0,string s=" | "){
        title=name;
        offhlight=ANSIBKG[BLACK];
        offtxt=ANSITXT[WHITE];
        hlight=ANSIBKG[DEFAULT];
        txt=ANSITXT[DEFAULT];
        fill=' ';
        dispWidth=0;
        dispHeight=0;
        align="left";
        beginX=1;
        beginY=1;
        sep=s;
        rows=0;
        cols=1;
        addRows(height+1);
        cols=0;
        addCols(width+1);
    }
    Table(string name="",size_t width=0,size_t height=0,string s=" | "){
        init(name,width,height,s);}
    void show (bool showHeaders=false,bool showBorder=true,bool hLight=true,int selX=-1,int selY=-1){
        cout << toString(showHeaders,showBorder,hLight,selX,selY).toString() << "\n";
    }
    mlstring toString(bool showHeaders=false,bool showBorder=true,bool hLight=true,int selX=-1,int selY=-1){
        string tmp;
        mlstring ret("");
        vector<size_t> widths(cols,0);
        for(int y = (showHeaders?0:beginY); y < rows; y++){
            for(int x = (showHeaders?0:beginX); x < cols; x++){
                widths.at(x)=max(widths.at(x),psize(cells.at(y).at(x)));
            }}
        string line=(hlight + txt);
        for(int y = (showHeaders?0:beginY); y < rows; y++){
            if((selX==-1&&selY==-1)&&((y%2)==0&&y!=0&&hLight)){
                line+=(offhlight+offtxt);
            }
            for(int x = (showHeaders?0:beginX); x < cols; x++){
                string tmp = cells.at(y).at(x);
                if(x==selX&&y==selY){line += offhlight + offtxt;}
                line += pad(tmp,widths.at(x),' ',align);
                if(x==selX&&y==selY){line += hlight + txt;}
                if(y==0&&x==0)line += FXUNDR;
                if(x==0)line+="|";
                else if(x+1<cols) line+=sep;
                if(x+1>=cols)line += NOUNDR;
            }
            if(selX==-1&&selY==-1&&(y%2)==0&&y!=0&&hLight){
                line+=(hlight+txt);
            }
            ret.lines.push_back(line);
            line="";
        }
        dispWidth = cols+(psize(sep)*(cols-1));
        for(int i = 0; i < widths.size(); i++){
            dispWidth += widths[i];
        }
        dispHeight= rows+(title!=""?2:0);
        if(showBorder){
            ret = addBorder(ret,(title+((selX!=-1)?" ("+to_string(selX)+","+to_string(selY)+")":"")));
            dispWidth+=2;
            dispHeight+=2;
            if(!showHeaders){
                dispWidth-=(widths.at(0)+psize(sep));
            }
        }
        return ret;
    }
    void addRows(size_t n){
        for(int i = 0; i < n; i++){
            cells.push_back(vector<string>(cols,fill));
            cells.at(cells.size()-1).at(0)=to_string(rows+i);
        }
        rows+=n;
    }
    void addCols(size_t n){
        for(int i = 0; i < cells.size(); i++){
            for(int j = 0; j < n; j++){
                cells.at(i).push_back((i==0)?to_string(cols+j+1):fill);
            }
        }
        cols+=n;
    }
    void set(size_t x, size_t y, string s){
		if (x >= cols || y >= rows) { throw runtime_error("out of table bounds"); }
        cells.at(y).at(x)=s;
    }

    void add(vector<string> row){
        addRows(1);
        while(row.size()>(cols-1)){
            addCols(1);
        }
        for(int x = 1; x <= row.size(); x++){
            set(x,rows-1,row.at(x-1));
        }
    }
    void add(initializer_list<string> row){
        vector<string> line = row;
        add(line);
    }
    void add(size_t cnt, string row[]){
        vector<string> line;
        for(int i = 0; i < cnt; i++){
            line.push_back(row[i]);}
        add(line);
    }
    void add(string a, string b){
        string row[2] = {a,b};
        add(2,row);
    }
    void add(string a, int b){
        add(a,to_string(b));}
    void add(string a, double b){
        add(a,niceDeci(b));}
    void add(string a, size_t b){
        add(a,to_string(b));}

    string& get(size_t x, size_t y){
        return cells.at(y).at(x);
    }
    string& operator()(size_t x, size_t y){
        return get(x,y);
    }
    void clear(){
        init();
    }
    void operator= (Table t){
        cells = t.cells;
        offhlight = t.offhlight;
        offtxt = t.offtxt;
        hlight = t.hlight;
        txt = t.txt;
        title = t.title;
        sep = t.sep;
        fill = t.fill;
        rows = t.rows;
        cols = t.cols;
        dispWidth = t.dispWidth;
        dispHeight = t.dispHeight;
    }
};

#endif /* TABLE_H */

#ifndef TABLE_H
#define TABLE_H

#include "Strings.h"
#include "Getch.h"
#include "Debugging.h"

/*
 * Nicely formatted table for output
 */
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
        fill=val;
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
        init(name,width,height,val,s);}
    
    Tuple<size_t,2> execMenu(bool showHeaders=false,bool showBorder=true,bool hLight=true){
        size_t x=1,y=1;
        char c=' ';
        do{
            if(c!=' '){
                for(int k = 0; k < dispHeight; k++){
                    cout << "\x1b[A";
                    for(int i = 0; i < dispWidth; i++){
                        cout << "\b \b";
                    }
                }
            }
            switch((int)c){
                case 104: //h, left
                    if(x!=1)x--;
                    else cout << "\a";
                    break;
                case 106: //j, down
                    if(y!=rows-1)y++;
                    else cout << "\a";
                    break;
                case 107: //k, up
                    if(y!=1)y--;
                    else cout << "\a";
                    break;
                case 108: //l, right
                    if(x!=cols-1)x++;
                    else cout << "\a";
                    break;
            }
            show(showHeaders,showBorder,hLight,x,y);
        }while((c=getch())!=' '&&c!='\n');
        return Tuple<size_t,2>(x,y);
    }
    void show(bool showHeaders=false,bool showBorder=true,bool hLight=true,size_t selX=-1,size_t selY=-1){
        mlstring s = toString(showHeaders,showBorder,hLight,selX,selY);
        cout << s.toString() << "\n";
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
        dispWidth = sum(widths)+cols+(psize(sep)*(cols-1));
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
        if(x>=cols||y>=rows){throw runtime_error(ErrForm() << "Cannot set cell: (" << x << ", " << y << ")" >> ErrForm::to_str);} 
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
    
    string get(size_t x, size_t y){
        return cells.at(y).at(x);
    }
    string operator()(size_t x, size_t y){
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


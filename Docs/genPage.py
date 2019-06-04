import os

def genTemplates:
    temps = {}
    with open("pageTemplate.html","r") as f:
        lines = f.readlines()
    body=""
    inblock = False
    for l in lines:
        if not inblock:
            if l[:4]=="<!--":
                title = l[4:-4]
                inblock = True
        else:
            if l[:8]=="<!-- end":
                temps[title]=body
                body=""
                inblock = False
            else:
                body+=l
    return temps

templates = genTemplates()

"""
File order:
includes
blurb
constants
methods/structs
"""

class page:
    def __init__(this, fname):
        this.name = fname
        with open(fname,"r") as f:
            lines = [n[:-1] for n in f.readlines()]

        html = templates["header"].replace("$NAME",this.name)
        k = 0 #line number

        #includes
        includes = []
        for i in range(k,len(lines)):
            k+=1
            if(lines[i][:8]=="#include"):
                includes.append(lines[i][9:])
            if(lines[i][:2]=="/*"):
                break
        packages= [x for x in includes if x[0]=="<"]
        modules = [os.path.basename(x[1:-1]) for x in includes if x not in modules]

        #blurb
        blurb=""
        for i in range(k,len(lines)):
            k+=1
            if(lines[i][:3]==" */"):
                break
            else:
                blurb+=lines[i]+"\n;
        html = html.replace("$BLURB",blurb)

        html += "\n\n"
        if(len(packages)+len(modules) > 0):
            html += "Also includes:\n"
        for n in modules:
            html += "<a href=\""+n+"tml\">"+n+"</a>\n"
        for n in packages:
            html += "&lt;" + n + "&gt;\n"

        html+= "\n"

        #constants
        consts = [n for n in lines if n[:5]=="const"]
        if(len(consts)>0):
            html += '<h3 style="display:inline">constants:</h3>\n'
        for n in consts:
            html += n + "\n"

        html += "\n"

        


    def __str__(self, level=0):
        ret = "\t"*level+repr(self.name)+"\n"
        for child in self.children:
            ret += child.__str__(level+1)
        return ret

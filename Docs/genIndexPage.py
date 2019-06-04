import re
from collections import defaultdict

indexTemplate = """<!DOCTYPE html>
<html>
    <head>
        <title>ArcherStandard</title>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    </head>
    <body>
        <h1><u>Archer&#39;s Standard Library</u></h1>
        <pre>
<h2 style="display:inline">Include Structure:</h2>
$DIAGRAM

Including the same file twice will give you a linker error, so be
careful to not include any file below another you've already
included. In addition, don't include any libraries (&lt;something&gt;)
if it is included by something else you've already included.

For example, you don't need to include &lt;iostream&gt; if you
include Table.h, since it imports Debugging.h which in turn
includes &lt;iostream&gt;.

To avoid any issues and to have access to the entire library,
simply include ArcherStandard.all.h, and be sure to not include
any of the following:
<b>
$INCLUDES
</b>
Don't worry, you can still use their contents.

If you only need access to a specific part of the library, you
can include just that file. Each file below it in the Diagram
will also be included.
        </pre>
    </body>
</html>"""

class Module:
    def __init__(self,fname):
        with open(fname,"r") as f:
            

def main():
    with open("IncludeDiagram.txt","r") as f:
        chart = ''.join(f.readlines())

        
    includes = [n[1:-1] for n in re.findall(r'<[^ >]*>',chart)]
    right = includes[:int(len(includes)/2)]
    left  = includes[int(len(includes)/2):]
    lsize = len(max(left, key=len))
    rsize = len(max(right, key=len))
    if(rsize < lsize):
        right, left = left, right
        lsize = rsize

    fmt = "<{}> {}  <{}>"
    pkgs = ""
    for (l,r) in zip(left, right):
        pkgs += (fmt.format(l," "*(lsize-len(l)),r)) + "\n"
    pkgs=pkgs[:-1].replace("<","&lt;").replace(">","&gt;")
    
    reps =  [['<','&lt;'],
             ['>','&gt;'],
             ['-&gt;','<font color="red">-&gt;</font>'],
             ['&lt;-','<font color="red">&lt;-</font>'],
             ['[','[<font color="red">'],
             [']','</font>]']]
    for n in reps:
        chart = chart.replace(n[0],n[1])
    pages = re.findall(r'\([^)]*\)',chart)
    for i in pages:
        chart = chart.replace(i,'<a href="Docs/'+i[1:-1]+'tml">'+i+'</a>')

    index = indexTemplate.replace("$DIAGRAM",chart).replace("$INCLUDES",pkgs)
    print(index)
    
main()

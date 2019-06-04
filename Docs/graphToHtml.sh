#!/bin/bash
cp IncludeDiagram.txt diagramHTML.txt
sed -i '' 's/</\&lt;/g' diagramHTML.txt
sed -i '' 's/>/\&gt;/g' diagramHTML.txt
sed -i '' 's/-&gt;/<font color="red">-\&gt;<\/font>/g' diagramHTML.txt
sed -i '' 's/&lt;-/<font color="red">\&lt;-<\/font>/g' diagramHTML.txt
sed -i '' 's/\[/[<font color="red">/' diagramHTML.txt
sed -i '' 's/\]/<\/font>\]/' diagramHTML.txt
sed -i '' 's/(\([^)]*\))/<a href="Docs\/\1tml">(\1)<\/a>/g' diagramHTML.txt

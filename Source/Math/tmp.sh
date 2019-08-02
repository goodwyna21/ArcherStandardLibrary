#!/bin/bash

for f in ./* ; do
    echo -e "\n"$f
    cat $f | grep "#include"
done


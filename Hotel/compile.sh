#!/bin/bash

OBJECTS = ""

for filename in ./*.cpp
do
    if [ "$filename" != "./main.cpp" ]; then
        echo $filename
        
        g++ -c -std=c++11 $filename
        
        OBJECT="."$(echo $filename| cut -d'.' -f 2)".o"

        OBJECTS+=" ${OBJECT}"
    fi
done

g++ $OBJECTS -std=c++11 main.cpp
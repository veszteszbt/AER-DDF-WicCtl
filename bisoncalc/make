#!/bin/bash

program=`pwd`
program=`basename $program`

case $1 in
    (bison)
        cd parser
        rm -f Parser.h Parserbase.h parse.cc Parser.ih
        bisonc++ grammar
        cd ..
    ;;
    (build)
        echo "g++ --std=c++17 -Wall -o commandline main.cc parser/parse.cc scanner/lex.cc"
        g++ --std=c++17 -Wall -o commandline main.cc parser/parse.cc scanner/lex.cc
    ;;
    (*)
        echo "use \"./make bison\" for grammar reset or \"./make build\" for build"
    ;;
esac
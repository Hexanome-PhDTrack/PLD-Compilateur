#!/bin/bash

# on Ubuntu, install the following packages:
#   -> antlr4
#   -> libantlr4-runtime-dev

# manual commands to run antlr then compile
#   ->$ antlr4 -visitor -no-listener -Dlanguage=Cpp ifcc.g4
#   ->$ clang++ -I /usr/include/antlr4-runtime -o exe *.cpp -lantlr4-runtime

A1="ANTLRJAR=/usr/share/java/stringtemplate4.jar:/usr/share/java/antlr4.jar:/usr/share/java/antlr4-runtime.jar:/usr/share/java/antlr3-runtime.jar/:/usr/share/java/treelayout.jar"
A2="ANTLRINC=/usr/include/antlr4-runtime"
A3="ANTLRLIB=-lantlr4-runtime"

make $A1 $A2 $A3 "$@"

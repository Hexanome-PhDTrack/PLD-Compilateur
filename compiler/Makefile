# You can override these from the command-line, as illustrated by the various `runmake_*.sh` scripts
ANTLRJAR=../antlr/jar/antlr-4.9.2-complete.jar
ANTLRINC=../antlr/include
ANTLRLIB=../antlr/lib/libantlr4-runtime.a

# TARGET specific parameters
include .env # https://simplernerd.com/make-env/

ifeq ($(TARGET),ubuntu)
  $(info TARGET set to ubuntu.)
  # default Ubuntu paths, using antlr4 and libantlr4-runtime-dev packages
  ANTLRJAR=/usr/share/java/stringtemplate4.jar:/usr/share/java/antlr4.jar:/usr/share/java/antlr4-runtime.jar:/usr/share/java/antlr3-runtime.jar/:/usr/share/java/treelayout.jar
  ANTLRINC=/usr/include/antlr4-runtime
  ANTLRLIB=-lantlr4-runtime
else ifeq ($(TARGET),fedora)
  $(info TARGET set to fedora.)
  ANTLRJAR=/usr/share/java/antlr4/antlr4.jar:/usr/share/java/antlr3-runtime.jar:/usr/share/java/antlr4/antlr4-runtime.jar:/usr/share/java/stringtemplate4/ST4.jar:/usr/share/java/treelayout/org.abego.treelayout.core.jar
  ANTLRINC=/usr/include/antlr4-runtime
  ANTLRLIB=/usr/lib64/libantlr4-runtime.so
endif

CC=g++
CCFLAGS=-g -c -std=c++17 -I$(ANTLRINC) -Wno-attributes # -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDFLAGS=-g

default: all
all: ifcc

##########################################
# link together all pieces of our compiler 
OBJECTS=build/main.o build/CodeGenVisitor.o build/ifccBaseVisitor.o build/ifccLexer.o build/ifccVisitor.o build/ifccParser.o 

ifcc: $(OBJECTS)
	@mkdir -p build
	$(CC) $(LDFLAGS) build/*.o $(ANTLRLIB) -o ifcc

##########################################
# compile our hand-writen C++ code: main(), CodeGenVisitor, etc.
build/%.o: %.cpp generated/ifccParser.cpp
	@mkdir -p build
	$(CC) $(CCFLAGS) -o $@ $< 

##########################################
# compile all the antlr-generated C++
build/%.o: generated/%.cpp
	@mkdir -p build
	$(CC) $(CCFLAGS) -o $@ $< 

##########################################
# generate the C++ implementation of our Lexer/Parser/Visitor
#
# cf https://stackoverflow.com/a/3077254/117814 for the multiple-file trick
generated/ifcc%.cpp: ifcc.g4
	@mkdir -p generated
	java -cp $(ANTLRJAR) org.antlr.v4.Tool  -visitor -no-listener -Dlanguage=Cpp -o generated ifcc.g4

# prevent automatic cleanup of "intermediate" files like ifccLexer.cpp etc
.PRECIOUS: generated/ifcc%.cpp   

##########################################
# view the parse tree in a graphical window

# Usage: `make gui FILE=path/to/your/file.c`
FILE ?= ../tests/testfiles/1_return42.c

gui:
	@mkdir -p generated build
	java -cp $(ANTLRJAR) org.antlr.v4.Tool -Dlanguage=Java -o generated ifcc.g4
	javac -cp $(ANTLRJAR) -d build generated/*.java
	java -cp $(ANTLRJAR):build org.antlr.v4.gui.TestRig ifcc axiom -gui $(FILE)

##########################################
# delete all machine-generated files
clean:
	rm -rf build generated
	rm -f ifcc

testvar:
	@echo $(TARGET)
	@echo $(ANTLRJAR)
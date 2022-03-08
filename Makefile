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



# paths
EXE=ifcc # name of executable
BIN_MAIN=bin/$(EXE)
INC_MAIN=inc/main
INC_GENERATED=inc/main/generated

# vars
ECHO = @echo # @echo hides this command in terminal, not its output

CC=g++
GDB_DEBUGGER_FLAGS=-g
PERSONAL_COMPIL_FLAGS=-D DEBUG -D COLORS # use own flags, see util.hpp
# use include files at compile time
CFLAGS=-I $(ANTLRINC) -I $(INC_MAIN) -I $(INC_GENERATED) -Wno-attributes $(PERSONAL_COMPIL_FLAGS) $(GDB_DEBUGGER_FLAGS) # -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDLIBS=-L $(ANTLRLIB) -lantlr4-runtime $(GDB_DEBUGGER_FLAGS)
LDFLAGS=--ansi --pedantic -Wall --std=c++17

SRCS_MAIN=$(wildcard src/main/**/*.cpp) $(wildcard src/main/*.cpp)
OBJS_MAIN=$(SRCS_MAIN:src/%.cpp=obj/%.o)

# at linking, give access to main/ to test files excluding the main main.
OBJ_MAIN_MAIN=obj/main/main.o

# targets and rules
# set default target : https://stackoverflow.com/questions/2057689/how-does-make-app-know-default-target-to-build-if-no-target-is-specified
.DEFAULT_GOAL := default
.PHONY: default build clean
# prevent automatic cleanup of "intermediate" files like ifccLexer.cpp etc
.PRECIOUS: src/main/generated/ifcc%.cpp

default: build

build: $(BIN_MAIN)

$(BIN_MAIN): $(OBJS_MAIN) # linking main
	@mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

obj/%.o: src/%.cpp # compiling main
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $^ $(CFLAGS)

# generate the C++ implementation of our Lexer/Parser/Visitor
# cf https://stackoverflow.com/a/3077254/117814 for the multiple-file trick
antlr: ifcc.g4
	@mkdir -p tmp
	java -cp $(ANTLRJAR) org.antlr.v4.Tool  -visitor -no-listener -Dlanguage=Cpp -o tmp ifcc.g4
	mv tmp/*.h inc/main/generated/
	mv tmp/*.cpp src/main/generated/

clean:
	rm -rf bin/* obj/* generated/* tmp/* inc/main/generated/* src/main/generated/*

run: $(BIN_MAIN)
	$(ECHO) "$(TURQUOISE_COLOR)*** Executing main *** $(NO_COLOR)"
	./$(BIN_MAIN)   



# TODO: make that with input parameter
# Usage: `make gui FILE=path/to/your/file.c`
FILE ?= ../tests/testfiles/1_return42.c

gui:
	@mkdir -p generated build
	java -cp $(ANTLRJAR) org.antlr.v4.Tool -Dlanguage=Java -o generated ifcc.g4
	javac -cp $(ANTLRJAR) -d build generated/*.java
	java -cp $(ANTLRJAR):build org.antlr.v4.gui.TestRig ifcc axiom -gui $(FILE)

testvar:
	@echo $(TARGET)
	@echo $(ANTLRJAR)
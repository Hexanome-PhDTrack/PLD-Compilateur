# echo -e colors
# WARN : don't put " and use the echo command, not echo -e
LIGHT_ORANGE_COLOR=\e[38;5;216m
LIGHT_YELLOW_COLOR=\e[38;5;220m
TURQUOISE_COLOR=\e[38;5;43m
LIGHT_BLUE_COLOR=\e[38;5;153m
RED_COLOR=\e[38;5;196m
NO_COLOR=\e[0m
BOLD=\e[1m
UNDERLINE=\e[4m

CONSTRUCTION_SIGN=🚧

# Determine this makefile's path.
# NOTE: used for recursive calls
# WARN: Be sure to place this BEFORE `include` directives, if any.
THIS_FILE := $(lastword $(MAKEFILE_LIST))

# You can override these from the command-line, as illustrated by the various `runmake_*.sh` scripts
ANTLRJAR=../antlr/jar/antlr-4.9.2-complete.jar
ANTLRINC=../antlr/include
ANTLRLIB=../antlr/lib/libantlr4-runtime.a

# TARGET specific parameters
include .env # https://simplernerd.com/make-env/

ifeq ($(TARGET),ubuntu)
  $(info 🎯 TARGET set to $(TARGET).)
  # default Ubuntu paths, using antlr4 and libantlr4-runtime-dev packages
  ANTLRJAR=/usr/share/java/stringtemplate4.jar:/usr/share/java/antlr4.jar:/usr/share/java/antlr4-runtime.jar:/usr/share/java/antlr3-runtime.jar/:/usr/share/java/treelayout.jar
  ANTLRINC=/usr/include/antlr4-runtime
  ANTLRLIB=-lantlr4-runtime
else ifeq ($(TARGET),fedora)
  $(info 🎯 TARGET set to $(TARGET).)
  ANTLRJAR=/usr/share/java/antlr4/antlr4.jar:/usr/share/java/antlr3-runtime.jar:/usr/share/java/antlr4/antlr4-runtime.jar:/usr/share/java/stringtemplate4/ST4.jar:/usr/share/java/treelayout/org.abego.treelayout.core.jar
  ANTLRINC=/usr/include/antlr4-runtime
  ANTLRLIB=/usr/lib64/libantlr4-runtime.so
else ifeq ($(TARGET),mac)
  $(info 🎯 TARGET set to $(TARGET).)
  ANTLRJAR=./antlr/jar/antlr-4.9.2-complete.jar
  ANTLRINC=./antlr/include
  ANTLRLIB=./antlr/lib/
endif

# paths
EXE=ifcc
BIN_MAIN=bin/$(EXE)
INC_MAIN=inc/main
INC_GENERATED=inc/main/generated

# vars
ECHO = @echo # @echo hides this command in terminal, not its output

CC=g++
GDB_DEBUGGER_FLAGS=-g
PERSONAL_COMPIL_FLAGS=-D DEBUG -D COLORS -std=c++17# use own flags, see util.hpp
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
.PHONY: default build message antlr clean run testvar ww rebuild rr clear gui tests
# prevent automatic cleanup of "intermediate" files like ifccLexer.cpp etc
.PRECIOUS: src/main/generated/ifcc%.cpp

default: build

build: message $(BIN_MAIN)

message:
	@echo "$(TURQUOISE_COLOR)$(CONSTRUCTION_SIGN) Compiling $(UNDERLINE)$(EXE)$(NO_COLOR)$(TURQUOISE_COLOR)...$(NO_COLOR)"
	@echo "$(LIGHT_ORANGE_COLOR)Have you run $(BOLD)make antlr$(NO_COLOR)$(LIGHT_ORANGE_COLOR) before?$(NO_COLOR)"

$(BIN_MAIN): $(OBJS_MAIN) # linking main
	@mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

obj/%.o: src/%.cpp # compiling main
	mkdir -p $(dir $@)
	$(CC) -o $@ -c $^ $(CFLAGS)

# generate the C++ implementation of our Lexer/Parser/Visitor
# cf https://stackoverflow.com/a/3077254/117814 for the multiple-file trick
antlr: ifcc.g4
	@echo "$(TURQUOISE_COLOR)$(CONSTRUCTION_SIGN) Generating $(UNDERLINE)ANTLR C++ files$(NO_COLOR)$(TURQUOISE_COLOR)...$(NO_COLOR)"
	@mkdir -p generated
	@mkdir -p src/main/generated
	@mkdir -p inc/main/generated
	java -cp $(ANTLRJAR) org.antlr.v4.Tool  -visitor -no-listener -Dlanguage=Cpp -o generated ifcc.g4
	mv generated/*.h inc/main/generated/
	mv generated/*.cpp src/main/generated/

clean:
	rm -rf bin/* obj/* generated/* inc/main/generated/* src/main/generated/*

run: $(BIN_MAIN)
	$(ECHO) "$(TURQUOISE_COLOR)$(CONSTRUCTION_SIGN) Executing $(UNDERLINE)$(EXE)$(NO_COLOR)$(TURQUOISE_COLOR)...$(NO_COLOR)"
	./$(BIN_MAIN)   

testvar:
	@echo $(TARGET)
	@echo $(ANTLRJAR)

ww: # where and what
	pwd
	ls -alt

rebuild:
	@$(MAKE) -f $(THIS_FILE) clean
	@$(MAKE) -f $(THIS_FILE) antlr
	@$(MAKE) -f $(THIS_FILE) build

rr: # rebuild and rerun (main)
	@$(MAKE) -f $(THIS_FILE) clean
	@$(MAKE) -f $(THIS_FILE) antlr
	@$(MAKE) -f $(THIS_FILE) build
	@$(MAKE) -f $(THIS_FILE) run

clear: # alias of clean
	@$(MAKE) -f $(THIS_FILE) clean


# TODO: make that with input parameter
# Usage: `make gui FILE=path/to/your/file.c`
FILE ?= tests/testfiles/1_return42.c

gui:
	@$(ECHO) "$(TURQUOISE_COLOR)$(CONSTRUCTION_SIGN) Generating $(UNDERLINE)ANTLR GUI$(NO_COLOR)$(TURQUOISE_COLOR)...$(NO_COLOR)"
	@mkdir -p generated build
	java -cp $(ANTLRJAR) org.antlr.v4.Tool -Dlanguage=Java -o generated ifcc.g4
	javac -cp $(ANTLRJAR) -d build generated/*.java
	java -cp $(ANTLRJAR):build org.antlr.v4.gui.TestRig ifcc axiom -gui $(FILE)

tests:
	@$(ECHO) "$(TURQUOISE_COLOR)$(CONSTRUCTION_SIGN) Running $(UNDERLINE)TESTS$(NO_COLOR)$(TURQUOISE_COLOR)...$(NO_COLOR)"
	rm -rf tests/ifcc-test-output/
	python3 tests/ifcc-test.py tests/testfiles/
	mv ifcc-test-output tests/
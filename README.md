# 🛠 PLD-Compilateur

## 🚧 Installation

### packages

> Ubuntu 20.04 LTS

Install the following packages through `apt get install <package>`.

* antlr4
* libantlr4-runtime-dev
* openjdk-11-jdk
* g++
* uuid-dev
* unzip
* cmake
* pkg-config

If using VSCode, install the following:

* clang

### visual studio code

If you use `VSCode`, install the following

* `ms-vscode.cpptools`: extention comming with GDB debugger integration.

## Compilation

1. `make antlr` to compile ANTLR4 files
2. `make` to compile the C++ files
3. `./bin/ifcc <path/file.c>` to use the produced executable.

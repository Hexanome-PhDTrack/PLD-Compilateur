# 🛠 PLD-Compilateur

## 🚧 Installation & set up

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

### .env file

Create a `.env` file at the root of the project. This file is used by the `Makefile` to determine the paths corresponding to a certain target/environnement.

* If you are on **Ubuntu** and are using the official ANTLR packages, create a `.env` file as follow:

```shell
TARGET=ubuntu
```

* If you are on **Fedora** and are using the official ANTLR packages, create a `.env` file as follow:

```shell
TARGET=fedora
```

* On other plateforms, or if you have downloaded directly ANTLR files using the `install-antlr.sh` script, just leave it empty since you are using the default settings.

## Using the Makefile

The `Makefile` contains many commands to build the project, generating ANTLR files or even testing the program.

To run the produced executables, run `./bin/ifcc <path/file.c>`.

> Note that all Makefile commands are supposed to be run at project root.

### Compiling the project

##### method 1 - modular approach (short)

1. `make antlr` to compile ANTLR4 files
2. `make` to compile the C++ files

> Once you have run `make antlr` once, you can skip it until you modify the grammar file or have cleaned generated files. Just jun `make`.

##### method 2 - clean, generate, build (long)

1. `make rebuild` to clean, regenerate ANTLR file the recompiling the executable.

### Running the tests

1. `make tests` to run the tests.

### Cleaning

1. `make clean` or `make clear` to delete generated, build and executable files.

### Using ANTLR Gui visualization

1. Make sure the ANTLR files are compiled. Use `make antlr` if it is not the case.
2. Run `make gui FILE=<file_path.c>` to run the ANTLR Gui analysis of the parsing on the provided FILE.

## Manual antlr4 and compiling

> Tested on Ubuntu 20.04 LTS

`antlr4 -visitor -no-listener -Dlanguage=Cpp ifcc.g4`: generate files using `antlr4`.

`clang++ -I /usr/include/antlr4-runtime -o exe *.cpp -lantlr4-runtime`: compile C++ code with `antlr4` dependencies.

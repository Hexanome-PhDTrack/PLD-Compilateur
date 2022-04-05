#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"
#include "Visitor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <regex>

using namespace antlr4;
using namespace std;



int main(int argn, const char **argv) {
    stringstream in;
    std::filebuf targetFileBuffer;

    // get input file
    std::string inputFileName = argv[1];
    ifstream fileStream(inputFileName);
    if(!fileStream.good()) {
        cout << "File not found. Please provide a valid file." << endl;
        return 1;
    }
    in << fileStream.rdbuf();

    std::string targetFileName;
    if (argn==2) {
        targetFileName = std::regex_replace(argv[1], std::regex(".c$"), ".s");
        targetFileBuffer.open(targetFileName,std::ios::out);
    }
    else if (argn == 3) {
        targetFileName = argv[2];
        targetFileBuffer.open(targetFileName,std::ios::out);
    }
    else
    {
        cerr << "usage: ifcc path/to/file.c path/to/file.s" << endl;
        exit(1);
    }



    ANTLRInputStream input(in.str());

    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();

    ifccParser parser(&tokens);
    tree::ParseTree* tree = parser.axiom();

    if(parser.getNumberOfSyntaxErrors() != 0)
    {
        cerr << "error: syntax error during parsing" << endl;
        exit(1);
    }

    Visitor v;
    int success = 1;
    success = v.visit(tree).as<int>();
    

    if(success == 0){
        if(targetFileBuffer.is_open()){
            std::ostream os(&targetFileBuffer);
            v.getIntermediateRepresentation().gen_asm(os);
        }
        else{
            std::ostream os(std::cout.rdbuf());
            v.getIntermediateRepresentation().gen_asm(os);
        }
    }

    if(targetFileBuffer.is_open()){
        targetFileBuffer.close();
    }

    // check generated file is not empty or composed only of whitespaces
    ifstream generatedFileStream(targetFileName);
    stringstream generatedFile;
    generatedFile << generatedFileStream.rdbuf();
    if(generatedFile.str().empty() || generatedFile.str() == " \n"){
        cerr << "error: generated file should not be empty." << endl;
        exit(1);
    }
    
    return success;
}

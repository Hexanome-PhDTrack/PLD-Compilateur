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
    ifstream fileStream(argv[1]);
    if(!fileStream.good()) {
        cout << "File not found. Please provide a valid file." << endl;
        return 1;
    }
    in << fileStream.rdbuf();

    if (argn==2) {
        std::string targetName(
            std::regex_replace(argv[1], std::regex(".c$"), ".s")
        );
        targetFileBuffer.open(targetName,std::ios::out);
    }
    else if (argn == 3) {
        std::string targetName(argv[2]);
        targetFileBuffer.open(targetName,std::ios::out);
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
    int success = v.visit(tree).as<int>();

    if(targetFileBuffer.is_open()){
        std::ostream os(&targetFileBuffer);
        v.getIntermediateRepresentation().gen_asm(os);
    }
    else{
        std::ostream os(std::cout.rdbuf());
        v.getIntermediateRepresentation().gen_asm(os);
    }
    
    if(targetFileBuffer.is_open()){
        targetFileBuffer.close();
    }
    
    return success;
}

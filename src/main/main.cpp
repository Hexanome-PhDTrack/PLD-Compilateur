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
    if (argn==2)
    {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }
    else
    {
        cerr << "usage: ifcc path/to/file.c" << endl ;
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
    return success;
}

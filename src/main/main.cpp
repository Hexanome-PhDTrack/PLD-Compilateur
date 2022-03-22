#include "antlr4-runtime.h"
#include "generated/ifccLexer.h"
#include "generated/ifccParser.h"
#include "generated/ifccBaseVisitor.h"
#include "CodeGenVisitor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <regex>

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
  stringstream in;
  std::filebuf targetFileBuffer;
  if (argn==2)
  {
    ifstream lecture(argv[1]);
    in << lecture.rdbuf();

    std::string targetName(std::regex_replace(argv[1], std::regex(".c$"), ".s"));
    targetFileBuffer.open(targetName,std::ios::out);
  }
  else if (argn == 3)
  {
    ifstream lecture(argv[1]);
    in << lecture.rdbuf();
    
    std::string targetName(argv[2]);
    targetFileBuffer.open(targetName,std::ios::out);
  }
  else
  {
      cerr << "usage: ifcc path/to/file.c path/to/file.s" << endl ;
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

  
  CodeGenVisitor v;
  if(targetFileBuffer.is_open()){
    v.setTargetFileBuffer(&targetFileBuffer);
  }
  else{
    v.setTargetFileBuffer(std::cout.rdbuf());
  }
  
  int success = v.visit(tree).as<int>();

  if(targetFileBuffer.is_open()){
    targetFileBuffer.close();
  }

  return success;
}

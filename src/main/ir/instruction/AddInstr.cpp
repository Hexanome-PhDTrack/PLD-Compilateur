#include "ir/instruction/AddInstr.h"

void AddInstr::gen_asm(std::ostream &o)
{
  o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
  o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
  o << "	addl "
    << "%edx, %eax \n";
  o << "	movl "
    << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
#include "ir/instruction/NegInstr.h"

void NegInstr::gen_asm(std::ostream &o)
{
  o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
  o << "    negl " << "%eax \n";
  o << "	movl " << "%eax, " <<  params.at(0).GetIndex() << "(%rbp) \n";
};
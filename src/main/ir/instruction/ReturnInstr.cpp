#include "ir/instruction/ReturnInstr.h"


void ReturnInstr::gen_asm(std::ostream &o)
{
  o << "	movl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
};
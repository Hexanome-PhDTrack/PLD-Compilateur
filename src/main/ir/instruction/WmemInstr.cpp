#include "ir/instruction/WmemInstr.h"

void WmemInstr::gen_asm(std::ostream &o)
{
    o << "	leaq " << params.at(1).GetIndex() << "(%rbp), %rax \n";
    o << "	movq "
      << "(%rax), " << params.at(0).GetIndex() << "(%rbp) \n";
};
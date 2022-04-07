#include "ir/instruction/BitComplementInstr.h"

void BitComplementInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
    o << "  notl %eax\n";
    o << "	movl "
      << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
}
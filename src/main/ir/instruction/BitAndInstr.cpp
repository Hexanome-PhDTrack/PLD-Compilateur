#include "ir/instruction/BitAndInstr.h"

void BitAndInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
    o << "	andl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
    o << "	movl "
      << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
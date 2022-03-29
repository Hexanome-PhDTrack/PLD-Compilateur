#include "ir/instruction/BitXor.h"

void BitAndInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
    o << "	xorl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
    o << "	movl " << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
#include "ir/instruction/BitXorInstr.h"

void BitXorInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
    o << "	xorl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
    o << "	movl " << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
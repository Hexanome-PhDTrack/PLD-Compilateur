#include "ir/instruction/BitNotInstr.h"

void BitNotInstr::gen_asm(std::ostream &o)
{
	o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
	o << "  notl "
	  << "%eax \n";
	o << "	movl "
	  << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
#include "ir/instruction/CmpLtInstr.h"

void CmpLtInstr::gen_asm(std::ostream &o)
{
	o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
	o << "	cmpl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
	o << "	setl "
	  << "%al";
	o << "	movzbl "
	  << "%al, %eax \n";
	o << "	movl "
	  << "%eax, " << params.at(0).GetIndex() << "(%rbp)\n";
};
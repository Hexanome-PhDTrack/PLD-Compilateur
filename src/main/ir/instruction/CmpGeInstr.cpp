#include "ir/instruction/CmpGeInstr.h"

void CmpGeInstr::gen_asm(std::ostream &o)
{
	o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
	o << "	cmpl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
	o << "	setge " << "%al \n";
	o << "	movzbl " << "%al, %eax \n";
	o << "	movl " << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
#include "ir/instruction/CmpEqInstr.h"

void CmpEqInstr::gen_x86_asm(std::ostream &o)
{
	o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
	o << "	cmpl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
	o << "	sete "
	  << "%al";
	o << "	movzbl "
	  << "%al, %eax \n";
	o << "	movl "
	  << "%eax, " << params.at(0).GetIndex() << "(%rbp)\n";
};

void CmpEqInstr::gen_arm_asm(std::ostream &o)
{

}
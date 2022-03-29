#include "ir/instruction/RmemInstr.h"

void RmemInstr::gen_asm(std::ostream &o)
{
	o << "	movq " << params.at(1).GetIndex() << "(%rbp), %rax \n";
	o << "	movl " << "(%rax), %eax \n";
	o << "	movl " << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
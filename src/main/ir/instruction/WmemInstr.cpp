#include "ir/instruction/WmemInstr.h"

void WmemInstr::gen_x86_asm(std::ostream &o)
{
	o << "	leaq " << params.at(1).GetIndex() << "(%rbp), %rax \n";
	o << "	movq "
	  << "(%rax), " << params.at(0).GetIndex() << "(%rbp) \n";
};

void WmemInstr::gen_arm_asm(std::ostream &o)
{

}
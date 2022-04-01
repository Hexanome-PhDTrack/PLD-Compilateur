#include "ir/instruction/CmpLeInstr.h"

void CmpLeInstr::gen_asm(std::ostream &o) {
	o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
	o << "	cmpl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
	o << "	setle "
		<< "%al \n";
	o << "	movzbl "
		<< "%al, %eax \n";
	o << "	movl "
		<< "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    
};
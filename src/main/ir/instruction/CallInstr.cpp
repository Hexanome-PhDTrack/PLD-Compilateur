#include "ir/instruction/CallInstr.h"

void CallInstr::gen_asm(std::ostream &o){
	o << "\tcall " << functionName << std::endl;
};
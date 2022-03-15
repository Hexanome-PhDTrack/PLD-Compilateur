#include "ir/instruction/CmpLeInstr.h"

void CmpLeInstr::gen_asm(std::ostream &o) {
	o<<"	cmp_le "<< params.at(0) << " " << params.at(1) << " " << params.at(2) <<"\n";
};
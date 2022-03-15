#include "ir/instruction/CmpEqInstr.h"

void CmpEqInstr::gen_asm(std::ostream &o) {
	o<<"	cmp_eq "<< params.at(0) << " " << params.at(1) << " " << params.at(2) <<"\n";
};
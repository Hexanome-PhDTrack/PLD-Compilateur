#include "ir/instruction/CmpLtInstr.h"

void CmpLtInstr::gen_asm(std::ostream &o) {
	o<<"	cmp_lt "<< params.at(0) << " " << params.at(1) << " " << params.at(2) <<"\n";
};
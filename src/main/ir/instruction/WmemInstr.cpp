#include "ir/instruction/WmemInstr.h"

void WmemInstr::gen_asm(std::ostream &o) {
	o<<"	wmem "<<params.at(0) << " " << params.at(1) <<"\n";
};
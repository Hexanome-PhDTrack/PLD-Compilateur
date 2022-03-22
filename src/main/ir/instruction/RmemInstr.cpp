#include "ir/instruction/RmemInstr.h"

void RmemInstr::gen_asm(std::ostream &o) {
	o<<"	rmem "<<params.at(0) << " " << params.at(1) << "\n";
};
#include "ir/instruction/CallInstr.h"

void CallInstr::gen_asm(std::ostream &o) {
	o<<"	call "<<params.at(0) <<"\n";
};
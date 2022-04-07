#include "ir/instruction/ControlStructInstr.h"

void ControlStructInstr::gen_asm(std::ostream &o) {
	o << "	cmpl $0, " << params.at(0).GetIndex() << "(%rbp)\n";
}
#include "ir/instruction/AddToRSPInstr.h"

void AddToRSPInstr::gen_asm(std::ostream& o) {
    o << "	addq $" << params.at(0).GetValue() << ", %rsp \n";
}
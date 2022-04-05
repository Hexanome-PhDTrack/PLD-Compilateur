#include "ir/instruction/SubToRSPInstr.h"

void SubToRSPInstr::gen_asm(std::ostream &o)
{
    o << "\tsubq $" << params.at(0).GetValue() << ", %rsp \n";
}
#include "ir/instruction/LdconstInstr.h"

void LdconstInstr::gen_asm(std::ostream &o)
{
    o << "	movl $" << params.at(1).GetValue() << ", " << params.at(0).GetIndex() << "(%rbp)\n";
};
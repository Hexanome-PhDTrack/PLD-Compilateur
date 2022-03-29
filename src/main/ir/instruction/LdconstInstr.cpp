#include "ir/instruction/LdconstInstr.h"

void LdconstInstr::gen_x86_asm(std::ostream &o)
{
    o << "	movl $" << params.at(1).GetValue() << ", " << params.at(0).GetIndex() << "(%rbp)\n";
};

void LdconstInstr::gen_arm_asm(std::ostream &o)
{

}
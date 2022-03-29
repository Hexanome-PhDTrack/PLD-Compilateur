#include "ir/instruction/CopyInstr.h"

void CopyInstr::gen_x86_asm(std::ostream &o)
{
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax\n";
    o << "	movl %eax, " << params.at(0).GetIndex() << "(%rbp)\n";
};

void CopyInstr::gen_arm_asm(std::ostream &o)
{

}
#include "ir/instruction/CopyInstr.h"

void CopyInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1) << "(%rbp), %eax\n"; // use eax => can't use movl on 2 stack pointer
    o << "	movl %eax, " << params.at(0) << "(%rbp)\n";
};
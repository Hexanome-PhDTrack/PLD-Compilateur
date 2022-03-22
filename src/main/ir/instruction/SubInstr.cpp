#include "ir/instruction/SubInstr.h"

void SubInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1) << "(%rbp), %eax \n";
    o << "	subl " << params.at(2) << "(%rbp), %eax \n";
    o << "  movl "
      << "%eax, " << params.at(0) << "(%rbp) \n";
};
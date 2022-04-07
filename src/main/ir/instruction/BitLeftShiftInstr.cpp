#include "ir/instruction/BitLeftShiftInstr.h"

void BitLeftShiftInstr::gen_asm(std::ostream &o)
{
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %edx \n";
    o << "	movl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
    o << "  movl %eax, %ecx\n";
    o << "  sall %cl, %edx\n";
    o << "  movl %edx, %eax\n";
    o << "	movl "
      << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
}
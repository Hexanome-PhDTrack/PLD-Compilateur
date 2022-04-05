#include "ir/instruction/BitNotInstr.h"

void BitNotInstr::gen_asm(std::ostream &o)
{
    o << "	cmpl $0, " << params.at(1).GetIndex() << "(%rbp)\n";
    o << "	sete %al\n";
    o << "  movzbl %al %eax\n";
    o << "	movl "
      << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
}
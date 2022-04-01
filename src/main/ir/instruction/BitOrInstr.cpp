#include "ir/instruction/BitOrInstr.h"

void BitOrInstr::gen_asm(std::ostream &o) {
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
    o << "	orl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
    o << "	movl "
      << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
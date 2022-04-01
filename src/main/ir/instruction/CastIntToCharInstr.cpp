#include "ir/instruction/CastCharToIntInstr.h"

void CastCharToIntInstr::gen_asm(std::ostream& o) {
    o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
    o << "	movb "
      << "%al, " << params.at(0).GetIndex() << "(%rbp) \n";
};
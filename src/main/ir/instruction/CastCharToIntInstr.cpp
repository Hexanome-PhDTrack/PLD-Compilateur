#include "ir/instruction/CastCharToIntInstr.h"

void CastCharToIntInstr::gen_asm(std::ostream& o) {
    o << "	movsbl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
    o << "	movl "
      << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
};
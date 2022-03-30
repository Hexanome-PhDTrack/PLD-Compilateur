#include "ir/instruction/RmemInstr.h"

void RmemInstr::gen_asm(std::ostream &o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // INT = *INT
    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT) {
        o << "	movq " << params.at(1).GetIndex() << "(%rbp), %rax \n";
        o << "	movl "
          << "(%rax), %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = *CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR) {
    }
    // CHAR = *INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT) {
    }
    // CHAR = *CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR) {
    }
};
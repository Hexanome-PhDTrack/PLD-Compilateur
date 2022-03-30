#include "ir/instruction/CmpGeInstr.h"

void CmpGeInstr::gen_asm(std::ostream &o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // INT = INT >= INT
    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT and
        params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	cmpl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	setge "
          << "%al \n";
        o << "	movzbl "
          << "%al, %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = INT >= CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
    // INT = CHAR >= INT
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
    }
    // INT = CHAR >= CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
    // CHAR = INT >= INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_INT) {
    }
    // CHAR = INT >= CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
    // CHAR = CHAR >= INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
    }
    // CHAR = CHAR >= CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
};
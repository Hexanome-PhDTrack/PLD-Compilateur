#include "ir/instruction/BitAndInstr.h"

void BitAndInstr::gen_asm(std::ostream &o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // INT = INT & INT
    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT and
        params.at(2).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax \n";
        o << "	andl " << params.at(2).GetIndex() << "(%rbp), %eax \n";
        o << "	movl "
          << "%eax, " << params.at(0).GetIndex() << "(%rbp) \n";
    }
    // INT = INT & CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
    // INT = CHAR & INT
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
    }
    // INT = CHAR & CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
    // CHAR = INT & INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_INT) {
    }
    // CHAR = INT & CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
    // CHAR = CHAR & INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_INT) {
    }
    // CHAR = CHAR & CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR and
             params.at(2).GetTypeName() == TYPE_CHAR) {
    }
};
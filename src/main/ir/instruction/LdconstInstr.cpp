#include "ir/instruction/LdconstInstr.h"

void LdconstInstr::gen_asm(std::ostream &o) {
    o << "	movl $" << params.at(1).GetValue() << ", "
      << params.at(0).GetIndex() << "(%rbp)\n";

    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // INT = INT
    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT) {
    }
    // INT = CHAR
    else if (params.at(0).GetTypeName() == TYPE_INT and
             params.at(1).GetTypeName() == TYPE_CHAR) {
    }
    // CHAR = INT
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_INT) {
    }
    // CHAR = CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR and
             params.at(1).GetTypeName() == TYPE_CHAR) {
    }
};
#include "ir/instruction/ReturnInstr.h"

void ReturnInstr::gen_asm(std::ostream &o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    // return INT
    if (params.at(0).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
    }
    // return CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR) {
    }
};
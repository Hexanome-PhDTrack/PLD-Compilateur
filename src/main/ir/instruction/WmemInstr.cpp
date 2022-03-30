#include "ir/instruction/WmemInstr.h"

void WmemInstr::gen_asm(std::ostream &o) {
    /**
     * There are multiple possibilities, depending of the types of the operand
     * and of the result.
     */

    if (params.at(0).GetTypeName() == TYPE_INT and
        params.at(1).GetTypeName() == TYPE_INT) {
        o << "	leaq " << params.at(1).GetIndex() << "(%rbp), %rax \n";
        o << "	movq "
          << "(%rax), " << params.at(0).GetIndex() << "(%rbp) \n";
    } else if (params.at(0).GetTypeName() == TYPE_CHAR and
               params.at(1).GetTypeName() == TYPE_CHAR) {
    }
    // else : error
};
#include "ir/instruction/MoveFunctionParamInstr.h"

void MoveFunctionParamInstr::gen_asm(std::ostream &o) {
    // Move an INT
    if (params.at(0).GetTypeName() == TYPE_INT) {
        o << "	movl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
        o << "	movl %eax, %" << argumentRegister << " \n";
    }
    // Move a CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR) {
        o << "	movsbl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
        o << "	movl %eax, %" << argumentRegister << " \n";
    }
};
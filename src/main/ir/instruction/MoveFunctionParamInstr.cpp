#include "ir/instruction/MoveFunctionParamInstr.h"

void MoveFunctionParamInstr::gen_asm(std::ostream &o) {
    if (!isMovingOnStack) {
        // moving via register
        // Move an INT
        if (params.at(0).GetTypeName() == TYPE_INT) {
            o << "	movl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
            o << "	movslq %eax, %" << argumentRegister << " \n";
        }
        // Move a CHAR
        else if (params.at(0).GetTypeName() == TYPE_CHAR) {
            o << "	movsbl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
            o << "	movslq %eax, %" << argumentRegister << " \n";
        }
    } else {
        // moving on stack
        // Move an INT
        if (params.at(0).GetTypeName() == TYPE_INT) {
            o << "	movl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
            o << "	pushq %rax" << " \n";
        }
        // Move a CHAR
        else if (params.at(0).GetTypeName() == TYPE_CHAR) {
            o << "	movsbl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
            o << "	pushq %rax" << " \n";
        }
    }
};
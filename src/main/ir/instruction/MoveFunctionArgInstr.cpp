#include "ir/instruction/MoveFunctionArgInstr.h"

void MoveFunctionArgInstr::gen_asm(std::ostream &o) {
    if (!isMovingOnStack) {
        // moving via register
        // Move an INT
        if(params.at(0).GetTypeName() == TYPE_INT) {
            o << "\tmovl " << fromParamRegister << ", " 
                << params.at(0).GetIndex() << "(%rbp)\n";
        }
        // Move a CHAR using %eax
        else if(params.at(0).GetTypeName() == TYPE_CHAR) {
            o << "\tmovl " << fromParamRegister << ", %eax\n";
            o << "\tmovb %al, " << params.at(0).GetIndex() << "(%rbp) \n";
        }
    } else {
        // moving on stack
        int oldStackFrameOffset = 16 + (argIndex - 6)*8;
        o << "\tmovl " << oldStackFrameOffset << "(%rbp), %eax\n";

        // Move an INT
        if (params.at(0).GetTypeName() == TYPE_INT) {
            o << "\tmovl %eax, " << params.at(0).GetIndex() << "(%rbp)\n";
        }
        // Move a CHAR
        else if (params.at(0).GetTypeName() == TYPE_CHAR) {
            o << "\tmovb %al, " << params.at(0).GetIndex() << "(%rbp)\n";
        }
    }
};
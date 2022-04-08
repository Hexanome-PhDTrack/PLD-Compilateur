#include "ir/instruction/MoveFunctionParamInstr.h"

// default: moving via register
MoveFunctionParamInstr::MoveFunctionParamInstr(
    Block *bb,
    std::vector<VarData> params,
    std::string argumentRegister,
    std::string scope
) : IRInstr(bb, IR_MoveFunctionParamInstr, params,scope)
{
    this->argumentRegister = argumentRegister;
};

// extra params moving via register
MoveFunctionParamInstr::MoveFunctionParamInstr(
    Block *bb,
    std::vector<VarData> params,
    VariableManager * variableManager,
    std::string scope
) : IRInstr(bb, IR_MoveFunctionParamInstr, params,scope) {
    this->isMovingOnStack = true;
    this->variableManager = variableManager;

    // correct stackFrameByteSize of the variableManager
    if (params.at(0).GetTypeName() == TYPE_INT) {
        // 1 quad == 8 bytes instead of 1 long (INT in C syntax) == 4 bytes
        variableManager->IncrementStackFrameByteSize(4);
    } else if (params.at(0).GetTypeName() == TYPE_CHAR) {
        // 1 quad == 8 bytes instead of 1 char (CHAR in C syntax) == 1 byte
        variableManager->IncrementStackFrameByteSize(6);
    }
};

void MoveFunctionParamInstr::gen_asm(std::ostream &o) {
    if (!isMovingOnStack) {
        // moving via register
        // Move an INT
        if (params.at(0).GetTypeName() == TYPE_INT) {
            o << "\tmovl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
            o << "\tmovslq %eax, %" << argumentRegister << " \n";
        }
        // Move a CHAR
        else if (params.at(0).GetTypeName() == TYPE_CHAR) {
            o << "\tmovsbl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
            o << "\tmovslq %eax, %" << argumentRegister << " \n";
        }
    } else {
        // moving on stack
        // Move an INT
        if (params.at(0).GetTypeName() == TYPE_INT) {
            o << "\tmovslq " << params.at(0).GetIndex() << "(%rbp), %rax \n";
            o << "\tpushq %rax" << " \n";
        }
        // Move a CHAR
        else if (params.at(0).GetTypeName() == TYPE_CHAR) {
            o << "\tmovsbq " << params.at(0).GetIndex() << "(%rbp), %rax \n";
            o << "\tpushq %rax" << " \n";
        }
    }
};
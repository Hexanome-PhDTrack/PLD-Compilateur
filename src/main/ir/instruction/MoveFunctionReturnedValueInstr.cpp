#include "ir/instruction/MoveFunctionReturnedValueInstr.h"

void MoveFunctionReturnedValueInstr::gen_asm(std::ostream &o)
{
    if (params.at(0).GetTypeName() == TYPE_INT) {
        o << "\tmovl %eax, " << params.at(0).GetIndex() << "(%rbp)\n";
    }
    // Move a CHAR
    else if (params.at(0).GetTypeName() == TYPE_CHAR) {
        o << "\tmovb %al, " << params.at(0).GetIndex() << "(%rbp)\n";
    }
}
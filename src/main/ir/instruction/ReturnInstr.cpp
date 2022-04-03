#include "ir/instruction/ReturnInstr.h"

void ReturnInstr::gen_asm(std::ostream &o) {
    if (params.at(0).GetTypeName() == TYPE_VOID || isVoidReturn)
    {
        o << "\tnop\n";
    }
    else {
        o << "\tmovl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
    }
};
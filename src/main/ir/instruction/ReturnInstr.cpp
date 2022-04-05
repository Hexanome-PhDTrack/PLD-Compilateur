#include "ir/instruction/ReturnInstr.h"

void ReturnInstr::gen_asm(std::ostream &o) {
    if (params.at(0).GetTypeName() == TYPE_VOID || isVoidReturn)
    {
        o << "\tnop\n";
    }
    else {
        o << "\tmovl " << params.at(0).GetIndex() << "(%rbp), %eax \n";
    }

    // multi return handling (return not in the end of the function)
    o << "\tjmp .end_" << functionName <<"\n"; // jump to end of function
};
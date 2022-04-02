#include "ir/instruction/CopyInstr.h"

void CopyInstr::gen_asm(std::ostream &o) {
    // only if the second computedVariable is not returned by a function
    // in that case, use %rax == %al directly
    if(!params.at(1).IsReturnedFromFunction()) {
        o << "	movl " << params.at(1).GetIndex() << "(%rbp), %eax\n";
    }
    
    o << "	movl %eax, " << params.at(0).GetIndex() << "(%rbp)\n";
};
#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"
#include "variable/VarData.h"
#include "ir/instruction/TypeIRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class IRInstr
{
public:
    IRInstr() {}; // default constructor
    IRInstr(
        Block *bb, 
        TypeIRInstr t, 
        std::vector<VarData> params,
        std::string scope
    ) : bb(bb), t(t), params(params),scope(scope) {};
    virtual ~IRInstr() = default; // WARN: Needed, make sure the destructor of the derived class is called

    virtual void gen_asm(std::ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */

protected:
    Block *bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
    TypeIRInstr t;
    std::vector<VarData> params;
    std::string scope;
};
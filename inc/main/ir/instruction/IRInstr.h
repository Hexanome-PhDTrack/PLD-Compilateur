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
    /**  constructor */
    IRInstr(Block *bb, TypeIRInstr t, std::vector<VarData> params) : bb(bb), t(t), params(params){};
    virtual ~IRInstr() = default; // WARN: Needed, make sure the destructor of the derived class is called

    /** Actual code generation */
    virtual void gen_asm(std::ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */
protected:
    Block *bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
    TypeIRInstr t;
    std::vector<VarData> params; //TODO: remove from IRInstr
};
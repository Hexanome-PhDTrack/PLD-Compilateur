#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"
#include "variable/VarData.h"

#include <vector>
#include <string>
#include <iostream>

class IRInstr
{
public:
    /**  constructor */
    IRInstr(Block *bb, TypeName t, std::vector<VarData> params) : bb(bb), t(t), params(params){};

    /** Actual code generation */
    virtual void gen_x86_asm(std::ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */
    virtual void gen_arm_asm(std::ostream &o);
    
protected:
    Block *bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
    TypeName t;
    std::vector<VarData> params;
};
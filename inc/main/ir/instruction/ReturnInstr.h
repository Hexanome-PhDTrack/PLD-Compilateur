#pragma once

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class ReturnInstr : public IRInstr
{
public:
    /**
     * @brief Construct a new Mul Instr object
     *
     * @param bb
     * @param t
     * @param params
     * return var1 -> first paramater : var1
     */
    ReturnInstr(
        Block *bb, 
        std::vector<VarData> params
    ) : IRInstr(bb, IR_ReturnInstr, params) {};

    virtual void gen_asm(std::ostream &o);
};
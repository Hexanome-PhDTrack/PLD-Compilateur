#pragma once

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class MulInstr : public IRInstr
{
public:
    /**
     * @brief Construct a new Mul Instr object
     *
     * @param bb
     * @param t
     * @param params
     * var1 = var2 * var3; => first parameter -> var1 | second parameter -> var2 | third parameter -> var3
     */
    MulInstr(Block *bb, TypeName t, std::vector<VarData> params) : IRInstr(bb, t, params){};

    virtual void gen_asm(std::ostream &o);
};
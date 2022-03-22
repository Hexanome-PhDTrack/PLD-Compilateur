#pragma once

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class SubInstr : public IRInstr
{
public:
    /**
     * @brief Construct a new Sub Instr object
     *
     * @param bb_
     * @param t
     * @param params
     * var1 = var2 - var3; => first parameter -> var1 | second parameter -> var2 | third parameter -> var3
     */
    SubInstr(Block *bb_, TypeName t, std::vector<std::string> params) : IRInstr(bb, t, params){};

    virtual void gen_asm(std::ostream &o);
};
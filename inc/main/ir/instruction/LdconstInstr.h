#pragma once

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class LdconstInstr : public IRInstr
{
public:
    /**
     * @brief Construct a new Ldconst Instr object
     *
     * @param bb
     * @param t
     * @param params
     * var = const; => first parameter -> var | second parameter -> const
     */
    LdconstInstr(Block *bb, TypeName t, std::vector<VarData> params) : IRInstr(bb, t, params){};

    virtual void gen_x86_asm(std::ostream &o);
    virtual void gen_arm_asm(std::ostream &o);
};
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
     * @param params
     * var = const; => first parameter -> var | second parameter -> const
     */
    LdconstInstr(
        Block *bb, 
        std::vector<VarData> params,
        std::string scope
    ) : IRInstr(bb, IR_LdconstInstr, params,scope) {};

    virtual void gen_asm(std::ostream &o);
};
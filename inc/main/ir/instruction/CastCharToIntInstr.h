#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

class CastCharToIntInstr : public IRInstr 
{
   public:
    /**
     * @brief Construct a new CastCharToInt Instr object
     *
     * @param bb
     * @param params
     * var1 = (int)var2; => first parameter -> var1 | second parameter -> var2
     */
    CastCharToIntInstr(
        Block *bb, 
        std::vector<VarData> params,
        std::string scope
    ) : IRInstr(bb, IR_CastCharToIntInstr, params,scope) {};

    virtual void gen_asm(std::ostream &o);
};
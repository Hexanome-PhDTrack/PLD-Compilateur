#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

class CastIntToCharInstr : public IRInstr {
   public:
    /**
     * @brief Construct a new CastIntToChar Instr object
     *
     * @param bb
     * @param t
     * @param params
     * var1 = (char)var2; => first parameter -> var1 | second parameter -> var2
     */
    CastIntToCharInstr(Block *bb, TypeName t, std::vector<VarData> params)
        : IRInstr(bb, t, params){};

    virtual void gen_asm(std::ostream &o);
};
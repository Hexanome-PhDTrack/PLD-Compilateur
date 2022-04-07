#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

class CastIntToCharInstr : public IRInstr 
{
   public:
        /**
         * @brief Construct a new CastIntToChar Instr object
         *
         * @param bb
         * @param params
         * var1 = (char)var2; => first parameter -> var1 | second parameter -> var2
         */
        CastIntToCharInstr(
            Block *bb, 
            std::vector<VarData> params
            ) : IRInstr(bb, IR_CastIntToCharInstr, params) {};

        virtual void gen_asm(std::ostream &o);
};
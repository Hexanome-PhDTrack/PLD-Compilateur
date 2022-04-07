#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class MoveFunctionReturnedValueInstr : public IRInstr
{
    public:
    /**
         * @brief Construct a new Bit Xor Instr object
         *
         * @param bb
         * @param params
         */
        MoveFunctionReturnedValueInstr(
            Block *bb,
            std::vector<VarData> params
        ) : IRInstr(bb, IR_MoveFunctionReturnedValueInstr, params) {};

        virtual void gen_asm(std::ostream &o);
};
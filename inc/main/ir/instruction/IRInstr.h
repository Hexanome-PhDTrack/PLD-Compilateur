#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class IRInstr{
    public:
        /**  constructor */
        IRInstr(Block* bb, TypeName t, std::vector<std::string> params): bb(bb), t(t), params(params){};
        
        /** Actual code generation */
        virtual void gen_asm(std::ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */
    protected:
        Block* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
        TypeName t;
        std::vector<std::string> params;
};
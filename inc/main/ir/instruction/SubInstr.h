#pragma once

#include "ir/instruction/IRInstr.h"
#include "ir/block/Block.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class SubInstr : public IRInstr{
    public:
        SubInstr(Block* bb_, TypeName t, std::vector<std::string> params): IRInstr(bb, t, params) {};

        virtual void gen_asm(std::ostream &o);

};
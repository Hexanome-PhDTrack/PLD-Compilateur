#pragma once

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class AddInstr : public IRInstr{
    public:
        AddInstr(Block* bb, TypeName t, std::vector<std::string> params): IRInstr(bb, t, params) {};

        virtual void gen_asm(std::ostream &o);

};
#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class RmemInstr : public IRInstr
{
	public:
		RmemInstr(Block* bb, TypeName t, std::vector<std::string> params) : IRInstr(bb, t, params) {};

		/** Actual code generation */
        virtual void gen_asm(std::ostream &o);
};

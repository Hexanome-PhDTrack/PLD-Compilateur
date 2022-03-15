#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class CmpLtInstr : public IRInstr
{
	public:
		CmpLtInstr(Block* bb, TypeName t, std::vector<std::string> params) : IRInstr(bb, t, params) {};

		/** Actual code generation */
        virtual void gen_asm(std::ostream &o);
};

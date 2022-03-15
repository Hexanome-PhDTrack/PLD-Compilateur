#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class CallInstr : public IRInstr
{
	public:
		CallInstr(Block* bb, TypeName t, std::vector<std::string> params) : IRInstr(bb, t, params) {};

		/** Actual code generation */
        virtual void gen_asm(std::ostream &o);
};

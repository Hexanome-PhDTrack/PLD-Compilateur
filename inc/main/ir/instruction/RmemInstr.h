#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class RmemInstr : public IRInstr
{
public:
	/**
	 * @brief Construct a new Rmem Instr object
	 *
	 * @param bb
	 * @param params
	 * var1 = *var2; => First parameter -> var1 | second parameter -> var 2
	 */
	RmemInstr(
		Block *bb, 
		std::vector<VarData> params,
        std::string scope
	) : IRInstr(bb, IR_RmemInstr, params,scope) {};

	virtual void gen_asm(std::ostream &o);
};

#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class WmemInstr : public IRInstr
{
public:
	/**
	 * @brief Construct a new Wmem Instr object
	 *
	 * @param bb
	 * @param t
	 * @param params
	 * *var1 = var2; => first parameter -> var1 | second parameter -> var2
	 */
	WmemInstr(
		Block *bb, 
		std::vector<VarData> params
	) : IRInstr(bb, IR_WmemInstr, params) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};

#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class CmpLtInstr : public IRInstr
{
public:
	/**
	 * @brief Construct a new Cmp Lt Instr object
	 *
	 * @param bb
	 * @param t
	 * @param params
	 * var1 = (var2 < var3); => first parameter -> var1 | second parameter -> var2 | third parameter -> var3
	 */
	CmpLtInstr(
		Block *bb, 
		std::vector<VarData> params
	) : IRInstr(bb, IR_CmpLtInstr, params) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};

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
	 * @param t
	 * @param params
	 * var1 = *var2; => First parameter -> var1 | second parameter -> var 2
	 */
	RmemInstr(Block *bb, TypeName t, std::vector<VarData> params) : IRInstr(bb, t, params){};

	/** Actual code generation */
	virtual void gen_x86_asm(std::ostream &o);
	virtual void gen_arm_asm(std::ostream &o);
};

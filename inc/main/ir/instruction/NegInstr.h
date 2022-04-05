#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class NegInstr : public IRInstr
{
public:
	/**
	 * @brief Construct a new Neg Instr object
	 *
	 * @param bb
	 * @param params
	 * var1 = -var2; => first parameter -> var1 | second parameter -> var2
	 */
	NegInstr(
		Block *bb, 
		std::vector<VarData> params,
        std::string scope
	) : IRInstr(bb, IR_NegInstr, params,scope) {};

	virtual void gen_asm(std::ostream &o);
};

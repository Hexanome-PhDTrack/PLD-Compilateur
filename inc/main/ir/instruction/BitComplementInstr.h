#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class BitComplementInstr : public IRInstr
{
public:
	/**
	 * @brief Construct a new Bitwise Complement Instr object
	 *
	 * @param bb
	 * @param params
	 * var1 = ~var2; => first parameter -> var1 | second parameter -> var2
	 */
	BitComplementInstr(
		Block *bb, 
		std::vector<VarData> params
	) : IRInstr(bb, IR_BitOrInstr, params){};

	virtual void gen_asm(std::ostream &o);
};

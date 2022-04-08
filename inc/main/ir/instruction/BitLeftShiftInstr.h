#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class BitLeftShiftInstr : public IRInstr
{
public:
	/**
	 * @brief Construct a new Bit Left Shift Instr object
	 *
	 * @param bb
	 * @param params
	 * var1 = var2 << var3; => first parameter -> var1 | second parameter -> var2 | third parameter -> var3
	 */
	BitLeftShiftInstr(
		Block *bb, 
		std::vector<VarData> params,
        std::string scope
	) : IRInstr(bb, IR_BitOrInstr, params,scope){};

	virtual void gen_asm(std::ostream &o);
};

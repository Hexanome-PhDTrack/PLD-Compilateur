#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class SubToRSPInstr : public IRInstr
{
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
	 * @param params
     */
	SubToRSPInstr(
		Block *bb,
        std::vector<VarData> params
	) : IRInstr(bb, TYPE_FUNCTION, params) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};
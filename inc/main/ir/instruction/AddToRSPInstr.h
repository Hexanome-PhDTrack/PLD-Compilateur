#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class AddToRSPInstr : public IRInstr
{
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
     * @param t the type of the instruction
	 * @param params
     */
	AddToRSPInstr(
		Block *bb,
        std::vector<VarData> params
	) : IRInstr(bb, IR_AddToRSPInstr, params) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};
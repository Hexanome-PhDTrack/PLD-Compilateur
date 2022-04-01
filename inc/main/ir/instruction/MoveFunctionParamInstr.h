#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class MoveFunctionParamInstr : public IRInstr
{
private:
	std::string argumentRegister;
	
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
     * @param t the type of the instruction
	 * @param params
	 */
	MoveFunctionParamInstr(
		Block *bb,
        TypeName t,
		std::vector<VarData> params,
        std::string argumentRegister
	) : IRInstr(bb, TYPE_FUNCTION, params), 
        argumentRegister(argumentRegister) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};
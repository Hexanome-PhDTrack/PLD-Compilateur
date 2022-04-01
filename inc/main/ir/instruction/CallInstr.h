#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class CallInstr : public IRInstr
{
private:
	std::string functionName;

public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
	 * @param functionName
	 * @param params
	 */
	CallInstr(
		Block *bb, 
		std::string functionName, 
		std::vector<VarData> params
	) : IRInstr(bb, IR_CallInstr, params),
		functionName(functionName) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};

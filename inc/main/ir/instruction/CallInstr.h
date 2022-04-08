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
		std::vector<VarData> params,
        std::string scope
	) : IRInstr(bb, IR_CallInstr, params,scope),
		functionName(functionName) {};

	virtual void gen_asm(std::ostream &o);
};

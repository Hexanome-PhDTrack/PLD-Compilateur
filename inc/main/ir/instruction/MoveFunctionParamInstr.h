#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"
#include "variable/VariableManager.h"

#include <vector>
#include <string>
#include <iostream>

class MoveFunctionParamInstr : public IRInstr
{
private:
    bool isMovingOnStack = false;
	std::string argumentRegister;
	VariableManager * variableManager = nullptr;
	
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
	 * @param params
     * @param argumentRegister the register to store the argument in, if needed (moving via register)
	 */
	// default: moving via register
	MoveFunctionParamInstr(
		Block *bb,
		std::vector<VarData> params,
        std::string argumentRegister,
        std::string scope
    );

	// extra params moving via register
	MoveFunctionParamInstr(
		Block *bb,
		std::vector<VarData> params,
        VariableManager * variableManager,
        std::string scope
    );

	virtual void gen_asm(std::ostream &o);
};
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
    bool isMovingOnStack;
	std::string argumentRegister;
	
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
     * @param t the type of the instruction
	 * @param params
     * @param isMovingOnStack whether the variable is moving on stack or not (via register)
     * @param argumentRegister the register to store the argument in, if needed (moving via register)
	 */
	MoveFunctionParamInstr(
		Block *bb,
		std::vector<VarData> params,
        bool isMovingOnStack,
        std::string argumentRegister
	) : IRInstr(bb, IR_MoveFunctionParamInstr, params),
        isMovingOnStack(isMovingOnStack), 
        argumentRegister(argumentRegister) {};

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};
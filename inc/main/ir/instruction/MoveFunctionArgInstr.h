#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class MoveFunctionArgInstr : public IRInstr
{
private:
    bool isMovingOnStack = false;
	std::string fromParamRegister;
    size_t argIndex; // mandatory for args moving on stack, to retreive their address
	
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
     * @param t the type of the instruction
	 * @param params
     * @param isMovingOnStack whether the variable is moving on stack or not (via register)
     * @param fromParamRegister the register to get the argument from, if needed (moving via register)
     * @param argIndex the index of the argument, if needed (moving via stack)
	 */
	MoveFunctionArgInstr(
		Block *bb,
		std::vector<VarData> params,
        std::string argumentRegister,
        size_t argIndex
	) : IRInstr(bb, IR_MoveFunctionArgInstr, params),
        isMovingOnStack(isMovingOnStack), 
        fromParamRegister(fromParamRegister),
        argIndex(argIndex) 
    {
        if(argIndex >= 6) {
            this->isMovingOnStack = true;
        }
    };

	/** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};
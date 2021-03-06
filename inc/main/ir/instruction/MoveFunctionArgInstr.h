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
    bool isMovingOnStack = false; // whether the variable is moving on stack or not (via register)
	std::string fromParamRegister;
    size_t argIndex; // mandatory for args moving on stack, to retreive their address
	
public:
/**
	 * @brief Construct a new Bit Xor Instr object
	 *
	 * @param bb
	 * @param params
     * @param isMovingOnStack 
     * @param fromParamRegister the register to get the argument from, if needed (moving via register)
     * @param argIndex the index of the argument, if needed (moving via stack)
	 */
	MoveFunctionArgInstr(
		Block *bb,
		std::vector<VarData> params,
        std::string fromParamRegister,
        size_t argIndex,
        std::string scope
	) : IRInstr(bb, IR_MoveFunctionArgInstr, params,scope),
        fromParamRegister(fromParamRegister),
        argIndex(argIndex) 
    {
        if(argIndex >= 6) {
            this->isMovingOnStack = true;
        }
    };

	virtual void gen_asm(std::ostream &o);
};
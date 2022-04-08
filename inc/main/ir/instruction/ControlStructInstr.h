#pragma once

#include "ir/instruction/IRInstr.h"

class ControlStructInstr : public IRInstr{
public:
    /**
	 * @brief Construct a new Cmp Instr object for the control (just compare a variable to 0 -> true = falseBlock, false = trueBlock)
	 *
	 * @param bb
	 * @param params
	 */
	ControlStructInstr(
		Block *bb, 
		std::vector<VarData> params,
        std::string scope
	) : IRInstr(bb, IR_ControlStructInstr, params,scope){};

	virtual void gen_asm(std::ostream &o);
};
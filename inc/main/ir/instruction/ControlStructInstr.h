#pragma once

#include "ir/instruction/IRInstr.h"

class ControlStructInstr : public IRInstr{
public:
    /**
	 * @brief Construct a new Cmp Instr object for the control (just compare a variable to 1)
	 *
	 * @param bb
	 * @param t
	 * @param params
	 */
	ControlStructInstr(Block *bb, TypeName t, std::vector<VarData> params) : IRInstr(bb, t, params){};

    /** Actual code generation */
	virtual void gen_asm(std::ostream &o);
};
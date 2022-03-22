#pragma once

#include "variable/TypeName.h"

//#include "ir/instruction/IRInstr.h"
class IRInstr; // circular import

#include <vector>
#include <string>
#include <iostream>

enum BlockLabel {
	BB_START,
	BB_END
};

class Block {
protected:
	BlockLabel label; /**< label of the BB, also will be the label in the generated code */
	std::vector<IRInstr*> instrs; /** < the instructions themselves. */

public:
	Block* exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
	Block* exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */

	Block(BlockLabel entry_label);
	~Block();

	void gen_asm(std::ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

	BlockLabel GetBlockLabel() { return label; }
	void SetBlockLabel(BlockLabel label) { this->label = label; }

	std::vector<IRInstr*> GetIRInstrs() { return instrs; }
	void AddIRInstr(IRInstr * instruction);
};
#pragma once

#include "ir/ControlFlowGraph.h"
#include "ir/instruction/IRInstr.h"

#include <vector>
#include <string>
#include <iostream>

class BasicBlock {
 public:
	BasicBlock(ControlFlowGraph* cfg, std::string entry_label);
	void gen_asm(std::ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

	void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);

	// No encapsulation whatsoever here. Feel free to do better.
	BasicBlock* exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
	BasicBlock* exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
	std::string label; /**< label of the BB, also will be the label in the generated code */
	ControlFlowGraph* cfg; /** < the CFG where this block belongs */
	std::vector<IRInstr*> instrs; /** < the instructions themselves. */
  	std::string test_var_name;  /** < when generating IR code for an if(expr) or while(expr) etc, store here the name of the variable that holds the value of expr */
};
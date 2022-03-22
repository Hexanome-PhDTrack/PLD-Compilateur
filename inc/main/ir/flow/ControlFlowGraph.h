#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"
#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

class ControlFlowGraph {
protected:
	VariableManager variableManager;
	int nextBBnumber; /**< just for naming */
	
	BlockManager blockManager;

public:
    ControlFlowGraph();
    ~ControlFlowGraph();

    void add_bb(Block* bb); 

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(std::ostream& o);
    std::string IR_reg_to_asm(std::string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    void gen_asm_prologue(std::ostream& o);
    void gen_asm_epilogue(std::ostream& o);

    // basic block management
    std::string new_BB_name();
    Block* current_bb;
};

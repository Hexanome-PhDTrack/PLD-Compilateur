#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "ir/block/BlockManager.h"


class ControlFlowGraph {
protected:
	VariableManager variableManager;
	int nextBBnumber; /**< just for naming */
	
	BlockManager blockManager;

public:
    ControlFlowGraph();
    ~ControlFlowGraph();

    void AddBlock(Block* bb); 

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(std::ostream& o);
    std::string IR_reg_to_asm(std::string name); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    void gen_asm_prologue(std::ostream& o);
    void gen_asm_epilogue(std::ostream& o);

    // symbol table methods
    void add_to_symbol_table(std::string name, TypeName t);
    std::string create_new_tempvar(TypeName t);
    bool isExist(std::string name);
    TypeName get_var_type(std::string name);
    bool removeTempVariable(std::string varName);

    // basic block management
    std::string new_BB_name();
};

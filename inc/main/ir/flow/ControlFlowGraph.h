#pragma once

#include "ir/block/Block.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

class ControlFlowGraph {
protected:
	std::map <std::string, TypeName> SymbolType; /**< part of the symbol table  */
	std::map <std::string, int> SymbolIndex; /**< part of the symbol table  */
	int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	int nextBBnumber; /**< just for naming */
	
	std::vector <Block*> blocks; /**< all the basic blocks of this CFG*/

public:
    ControlFlowGraph();
    ~ControlFlowGraph();

    void add_bb(Block* bb); 

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(std::ostream& o);
    std::string IR_reg_to_asm(std::string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    void gen_asm_prologue(std::ostream& o);
    void gen_asm_epilogue(std::ostream& o);

    // symbol table methods
    void add_to_symbol_table(std::string name, TypeName t);
    std::string create_new_tempvar(TypeName t);
    int get_var_index(std::string name);
    TypeName get_var_type(std::string name);

    // basic block management
    std::string new_BB_name();
    Block* current_bb;
};

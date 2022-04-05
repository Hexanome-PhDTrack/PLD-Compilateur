#pragma once

#include "variable/VarData.h"
#include "variable/VariableManager.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>
#include <map>

class Function; // circular import
/* {
    public:
        std::string GetName();
};*/
class Block; // circular import
class BlockManager; // circular import

class ControlFlowGraph {
    protected:
        VariableManager * variableManager;
        BlockManager * blockManager; // delete this
        Block * firstBlock;
        Function * function;
        int nextBBnumber = 0;

    public:
        ControlFlowGraph(Function * function);
        ~ControlFlowGraph();
        Block* AddBlock();
        // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
        void gen_asm(std::ostream& o);
        std::string IR_reg_to_asm(std::string name, std::string scope); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
        
        // symbol table methods
        VariableManager * getVariableManager();
        VarData add_to_symbol_table(std::string name, size_t lineNumber, TypeName t, std::string scope);
        VarData add_const_to_symbol_table(std::string name, size_t lineNumber, TypeName t, int value, std::string scope);
        VarData getVariable(std::string name, std::string scope);
        bool isExist(std::string name, std::string scope);
        TypeName get_var_type(std::string name, std::string scope);
        bool removeTempVariable(VarData var);
        Block* getFirstBlock(){
            return firstBlock;
        }
        std::string new_BB_name();

        // getters
        inline Function * GetFunction() {
            return function;
        }
};

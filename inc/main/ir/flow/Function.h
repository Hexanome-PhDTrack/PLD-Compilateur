#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

#include <string>
#include <iostream>

class Function {
    private:
        std::string name = "";

        ControlFlowGraph * cfg;

        TypeName returnType;
        
    public:
        ControlFlowGraph * getControlFlowGraph();
        void gen_asm(std::ostream& o);
        void gen_asm_prologue(std::ostream& o);
        void gen_asm_epilogue(std::ostream& o);

        std::string getName();

        TypeName getReturnType();

        Function(std::string name, TypeName returnType);
        ~Function();
};
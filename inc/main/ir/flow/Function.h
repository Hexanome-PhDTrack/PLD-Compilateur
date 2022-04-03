#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>

class Function {
    private:
        std::string name = "";

        ControlFlowGraph * cfg;

        std::vector<std::string> argumentNames;
        TypeName returnType;
        
    public:
        ControlFlowGraph * getControlFlowGraph();
        void gen_asm(std::ostream& o);
        void gen_asm_prologue(std::ostream& o);
        void gen_asm_epilogue(std::ostream& o);

        std::string GetName();
        void AddArgument(std::string arg, size_t lineNumber, TypeName type);
        VarData GetArgument(std::string arg);
        size_t GetArgumentIndex(std::string arg);
        std::vector<std::string> GetArgumentNames();
        std::vector<std::pair<std::string, VarData>> GetArguments();

        TypeName getReturnType();

        Function(std::string name, TypeName returnType);
        ~Function();
};
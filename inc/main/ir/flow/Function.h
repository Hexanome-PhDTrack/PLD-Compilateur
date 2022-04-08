#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>

class ControlFlowGraph; // circular dependency

class Function {
    private:
        std::string name = "";

        ControlFlowGraph * cfg;

        std::vector<std::string> argumentNames;
        TypeName returnType;
        bool isVariadic = false;

        void gen_asm_vsum(std::ostream &o);
        
    public:
        ControlFlowGraph * getControlFlowGraph();
        void gen_asm(std::ostream& o);
        void gen_asm_prologue(std::ostream& o);
        void gen_asm_epilogue(std::ostream& o);

        std::string GetName();
        VarData AddArgument(
            std::string arg, 
            size_t lineNumber, 
            TypeName type, std::string scope
        );
        VarData GetArgument(std::string arg, std::string scope);
        size_t GetArgumentIndex(std::string arg);
        VarData GetArgumentByIndex(size_t index);
        std::vector<std::string> GetArgumentNames();
        std::vector<std::pair<std::string, VarData>> GetArguments(std::string scope);
        inline bool IsVariadic() { return isVariadic; }
        inline void SetVariadic(bool variadic) { this->isVariadic = variadic; }
        inline size_t GetArgumentCount() { return argumentNames.size(); }

        TypeName getReturnType();

        Function(std::string name, TypeName returnType);
        ~Function();
};
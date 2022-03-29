#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

#include <string>

class Function {
    public:
        ControlFlowGraph& getControlFlowGraph();

        std::string getName();

        TypeName getReturnType();

        Function(std::string name, TypeName returnType) : name(name), returnType(returnType){};

    private:
        std::string name;

        ControlFlowGraph cfg;

        TypeName returnType;
};
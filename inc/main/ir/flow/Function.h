#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

class Function {
    public:
        ControlFlowGraph& getControlFlowGraph();
        TypeName getReturnType();

        Function(TypeName returnType) : returnType(returnType){};

    private:
        ControlFlowGraph cfg;

        TypeName returnType;
};
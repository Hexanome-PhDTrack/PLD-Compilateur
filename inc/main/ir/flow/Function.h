#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

class Function {
    public:
        VariableManager & getVariableManager() ;
        ControlFlowGraph& getControlFlowGraph();
        TypeName getReturnType();

        Function(TypeName returnType) : returnType(returnType){};

    private:
        VariableManager variableManager;
        ControlFlowGraph cfg;

        TypeName returnType;
};
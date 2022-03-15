#pragma once

#include "variable/VariableManager.h"
#include "ir/block/BlockManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "variable/TypeName.h"

class Function {
private:
    VariableManager variableManager;
    ControlFlowGraph cfg;

    TypeName returnType;
};
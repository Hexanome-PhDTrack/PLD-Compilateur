#include "ir/flow/Function.h"

VariableManager & Function::getVariableManager() {
    return variableManager;
}

ControlFlowGraph & Function::getControlFlowGraph() {
    return cfg;
}

TypeName Function::getReturnType(){
    return returnType;
}
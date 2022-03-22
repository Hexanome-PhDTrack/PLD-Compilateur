#include "ir/flow/Function.h"

ControlFlowGraph & Function::getControlFlowGraph() {
    return cfg;
}

TypeName Function::getReturnType(){
    return returnType;
}
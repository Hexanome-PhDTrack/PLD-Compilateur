#include "ir/flow/Function.h"

std::string Function::getName(){
    return name;
}

ControlFlowGraph & Function::getControlFlowGraph() {
    return cfg;
}

TypeName Function::getReturnType(){
    return returnType;
}
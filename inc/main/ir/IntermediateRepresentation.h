#pragma once

#include "ir/flow/Function.h"
#include "ir/block/Block.h"
#include "ir/flow/CallData.h"

#include <vector>

class IntermediateRepresentation {
private:
    std::vector<Function*> functions; 
    std::vector<CallData*> calls; // deleted elsewhere

public:
    IntermediateRepresentation() {}
    ~IntermediateRepresentation() {}

    void AddFunction(Function* function);

    void AddCall(CallData* call);

};
#include "ir/IntermediateRepresentation.h"

IntermediateRepresentation::~IntermediateRepresentation() {
    for(int i = 0; i < functions.size(); i++){
        delete functions[i];
    }
    // do not dete calls, all their data is deleted elsewhere
    //    + caller, callee deleted in loop above
    //    + callBlock deleted in CFG destructor
}

void IntermediateRepresentation::AddCall(CallData* call) {
    calls.push_back(call);
}

void IntermediateRepresentation::AddFunction(Function* function) {
    functions.push_back(function);
}
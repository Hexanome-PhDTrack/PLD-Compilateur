#include "ir/IntermediateRepresentation.h"

IntermediateRepresentation::~IntermediateRepresentation() {
    for(int i = 0; i < functionsToDelete.size(); i++){
        delete functionsToDelete[i];
    }
    // do not dete calls, all their data is deleted elsewhere
    //    + caller, callee deleted in loop above
    //    + callBlock deleted in CFG destructor
}

void IntermediateRepresentation::AddCall(CallData* call) {
    calls.push_back(call);
}

void IntermediateRepresentation::AddFunction(std::string name, Function* function) {
    functions.insert(
        std::pair<std::string, Function*>(
            name,
            function
        )
    );

    functionsToDelete.push_back(function);
}

Function * IntermediateRepresentation::getFunction(std::string name){
    return functions.find(name)->second;
}

void IntermediateRepresentation::gen_asm(std::ostream &o){
    //getFunction("main") -> getControlFlowGraph() -> gen_asm(o);
    getFunction("main")->gen_asm(o);
}
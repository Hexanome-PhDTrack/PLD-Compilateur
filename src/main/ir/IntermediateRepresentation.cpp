#include "ir/IntermediateRepresentation.h"

IntermediateRepresentation::IntermediateRepresentation() {
    // add known functions
    // add putchar
    Function * putchar = new Function("putchar", TYPE_VOID);
    AddFunction("putchar", putchar);

    // add getchar
    Function * getchar = new Function("getchar", TYPE_CHAR);
    AddFunction("getchar", getchar);
}

IntermediateRepresentation::~IntermediateRepresentation() {
    for(int i = 0; i < (int)functionsToDelete.size(); i++){
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

std::vector<Function*> IntermediateRepresentation::getAllFunctions(){
    return functionsToDelete;
}

void IntermediateRepresentation::gen_asm(std::ostream &o){
    //getFunction("main") -> getControlFlowGraph() -> gen_asm(o);
    getFunction("main")->gen_asm(o);
}
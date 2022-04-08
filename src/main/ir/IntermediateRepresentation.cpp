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
    for (auto function : functionsToDelete) {
        delete function;
    }
    // do not delete calls, all their data is deleted elsewhere
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

Function * IntermediateRepresentation::getFunction(std::string name) {
    auto found = functions.find(name);
    Function * function = nullptr;

    // check function was found
    if (found != functions.end()) {
        function = found->second;
    }

    return function;
}

std::vector<Function*> IntermediateRepresentation::getAllFunctions(){
    return functionsToDelete;
}

void IntermediateRepresentation::gen_asm(std::ostream &o){
    //getFunction("main")->gen_asm(o);
    // generate asm for all functions
    for (auto function : getAllFunctions()) {
        function->gen_asm(o);
    }
}
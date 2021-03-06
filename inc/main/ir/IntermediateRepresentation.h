#pragma once

#include "ir/flow/Function.h"
#include "ir/block/Block.h"
#include "ir/flow/CallData.h"

#include <vector>
#include <map>

class IntermediateRepresentation {
private:
    std::map<std::string, Function*> functions; // WARNING : don't delete this
    std::vector<Function*> functionsToDelete; // delete this

    std::vector<CallData*> calls; // deleted elsewhere

public:
    IntermediateRepresentation(); // initialize known functions
    ~IntermediateRepresentation();

    void AddFunction(std::string name, Function* function);

    void AddCall(CallData* call);

    /**
     * @brief Get the Function object by the name
     * 
     * @param name the name
     * @return Function* 
     */
    Function * getFunction(std::string name);
    inline std::map<std::string, Function*> GetFunctions() {
        return functions;
    }

    /**
     * @brief Get the All Functions object
     * 
     * @return std::vector<Function*> 
     */
    std::vector<Function*> getAllFunctions();

    void gen_asm(std::ostream &o);
};
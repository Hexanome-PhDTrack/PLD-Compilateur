#pragma once

#include "warning/Warning.h"
#include "variable/VarData.h"

class UnusedVariableWarning : public Warning {
public:
    UnusedVariableWarning(
        VarData & varData
    ){
        message = "The variable " + varData.GetVarName() + " is unused";
    }
    ~UnusedVariableWarning() {}
};
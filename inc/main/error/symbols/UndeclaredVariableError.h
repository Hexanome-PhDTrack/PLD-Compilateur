#pragma once

#include "error/Error.h"
#include "variable/VarData.h"

class UndeclaredVariableError : public Error {
public:
    UndeclaredVariableError(
        VarData & varData
    ){
        message = "The variable " + varData.GetVarName() + " is never declared";
    }
    ~UndeclaredVariableError() {}
};
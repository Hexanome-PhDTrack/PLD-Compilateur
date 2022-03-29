#pragma once

#include "error/CustomError.h"
#include "variable/VarData.h"

class UndeclaredVariableError : public CustomError {
public:
    UndeclaredVariableError(
        VarData & varData
    ){
        message = "The variable " + varData.GetVarName() + " is never declared";
    }
    ~UndeclaredVariableError() {}
};
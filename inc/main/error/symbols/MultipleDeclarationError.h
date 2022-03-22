#pragma once

#include "error/CustomError.h"
#include "variable/VarData.h"

class MultipleDeclarationError : public CustomError {
public:
    MultipleDeclarationError(
        VarData & varData
    ){
        message = "The variable " + varData.GetVarName() + " is declared multiple times";
    }
    ~MultipleDeclarationError() {}
};
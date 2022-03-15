#pragma once

#include "error/Error.h"
#include "variable/VarData.h"

class MultipleDeclarationError : public Error {
public:
    MultipleDeclarationError(
        VarData & varData
    ){
        message = "The variable " + varData.GetVarName() + " is declared multiple times";
    }
    ~MultipleDeclarationError() {}
};
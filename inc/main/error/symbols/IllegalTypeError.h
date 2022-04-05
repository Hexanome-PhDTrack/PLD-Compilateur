#pragma once

#include "error/CustomError.h"
#include "variable/VarData.h"

class IllegalTypeError : public CustomError {
public:
    IllegalTypeError(
        VarData & varData
    ){
        message = "Invalid type used on line " + std::to_string(varData.GetLineNumber()) + ": " + getStringFromTypeName(varData.GetTypeName());
    }
    ~IllegalTypeError() {}
};
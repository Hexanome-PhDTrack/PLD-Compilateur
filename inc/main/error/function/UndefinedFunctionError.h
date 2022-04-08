#pragma once

#include "error/CustomError.h"
#include "ir/flow/Function.h"

class UndefinedFunctionError : public CustomError {
    public:
        UndefinedFunctionError(
            std::string functionName
        ){
            message = "The function " 
                + functionName
                + " is unknown.";
        }
        ~UndefinedFunctionError() {}
};

#pragma once

#include "error/CustomError.h"
#include "ir/flow/Function.h"

class WrongNumberOfParamsError : public CustomError {
    public:
        WrongNumberOfParamsError(
            Function & function,
            int paramCount, 
            int expectedArgCount
        ) {
            message = "The call to the function " 
                + function.GetName() 
                + " is invalid. "
                + std::to_string(paramCount) + 
                " parameters were passed, but "
                + std::to_string(expectedArgCount) 
                + " were expected.";
        }
        ~WrongNumberOfParamsError() {}
};

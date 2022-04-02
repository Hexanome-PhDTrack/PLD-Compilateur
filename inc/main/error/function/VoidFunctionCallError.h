#pragma once

#include "error/CustomError.h"
#include "ir/flow/Function.h"

class VoidFunctionCallError : public CustomError {
    public:
        VoidFunctionCallError(
            Function & function
        ){
            message = "The function " 
                + function.GetName() 
                + " is declared as void."
                + " It cannot be used to retreive a value.";
        }
        ~VoidFunctionCallError() {}
};

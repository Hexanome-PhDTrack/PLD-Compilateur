#pragma once

#include "warning/Warning.h"
#include "ir/flow/Function.h"

class ReturnTypeWarning : public Warning {
public:
    ReturnTypeWarning(
        Function & function
    ){
        message = "Return type does not match function"
            + function.GetName() 
            + " return type.";
    }
    ~ReturnTypeWarning() {}
};
#pragma once

#include "warning/Warning.h"
#include "ir/flow/Function.h"

class ParamTypeMismatchWarning : public Warning {
public:
    ParamTypeMismatchWarning(
        Function & function,
        std::string paramName,
        std::string paramType,
        std::string expectedType
    ){
        message = "The parameter " 
        + paramName + " of the function " 
        + function.GetName() + " has the type " 
        + paramType + ", but " + expectedType + " was expected.";
    }
    ~ParamTypeMismatchWarning() {}
};
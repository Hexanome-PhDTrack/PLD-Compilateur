#pragma once

#include "warning/Warning.h"
#include "variable/VarData.h"

class DividingByZeroWarning : public Warning {
public:
    DividingByZeroWarning(
        const VarData & varData
    ){
        message = "Dividing by zero in line "  + std::to_string(varData.GetLineNumber());
    }
    ~DividingByZeroWarning() {}
};
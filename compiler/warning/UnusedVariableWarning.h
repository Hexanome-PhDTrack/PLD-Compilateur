#pragma once

#include "Warning.h"
#include "../variable/VarData.h"

class UnusedVariableWarning : public virtual Warning {
private: 
    VarData & varData;

public:
    UnusedVariableWarning(
        VarData & varData
    ): 
        Warning("WARNING: Unused variable."), 
        varData(varData) 
    {

    }
    ~UnusedVariableWarning();

    inline void Log() {
        std::cout << this->warningMessage << std::endl;
        std::cout << "    " << varData.ToString() << std::endl;
    }
};
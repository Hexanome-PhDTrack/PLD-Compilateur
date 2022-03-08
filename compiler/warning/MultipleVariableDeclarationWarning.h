#pragma once

#include "Warning.h"
#include "../variable/VarData.h"

class MultipleVariableDeclarationWarning : public virtual Warning {
private: 
    VarData & varData;

public:
    MultipleVariableDeclarationWarning(
        VarData & varData
    ): 
        Warning("WARNING: Multiple declarations of variable."), 
        varData(varData) 
    {

    }
    ~MultipleVariableDeclarationWarning();

    inline void Log() {
        std::cout << this->warningMessage << std::endl;
        std::cout << "    " << varData.ToString() << std::endl;
    }
};
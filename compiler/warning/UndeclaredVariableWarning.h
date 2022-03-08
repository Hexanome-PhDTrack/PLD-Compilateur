#pragma once

#include "Warning.h"
#include "../variable/VarData.h"

class UndeclaredVariableWarning : public virtual Warning {
private: 
    VarData & varData;

public:
    UndeclaredVariableWarning(
        VarData & varData
    ): 
        Warning("WARNING: Variable used but never declared."), 
        varData(varData) 
    {
        
    }
    ~UndeclaredVariableWarning();

    inline void Log() {
        std::cout << this->warningMessage << std::endl;
        std::cout << "    " << varData.ToString() << std::endl;
    }
};
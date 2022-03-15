#pragma once

#include "warning/Warning.h"
#include "warning/UnusedVariableWarning.h"
#include "variable/VarData.h"
#include "variable/VariableManager.h"

#include <vector>

class WarningManager {
private:
    std::vector<Warning*> warnings;

    void checkUnusedVariable(VariableManager & varManager);

public:
    WarningManager() {}
    ~WarningManager();

    void LogWarnings();
    inline void CheckWarnings(VariableManager & varManager) {
        checkUnusedVariable(varManager);
    }

    inline void AddWarning(Warning* warning) {
        warnings.push_back(warning);
    }
};
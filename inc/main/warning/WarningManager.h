#pragma once

#include "warning/Warning.h"
#include "warning/UnusedVariableWarning.h"
#include "variable/VarData.h"
#include "variable/VariableManager.h"
#include "ir/IntermediateRepresentation.h"
#include "ir/flow/Function.h"

#include <vector>

class WarningManager {
private:
    std::vector<Warning*> warnings;

    void checkUnusedVariable(IntermediateRepresentation & ir);

public:
    WarningManager() {}
    ~WarningManager();

    void LogWarnings();
    inline void CheckWarnings(IntermediateRepresentation & ir) {
        checkUnusedVariable(ir);
    }

    inline void AddWarning(Warning* warning) {
        warnings.push_back(warning);
    }
};
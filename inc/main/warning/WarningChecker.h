#pragma once

#include "Warning.h"
#include "UnusedVariableWarning.h"
#include "CodeGenVisitor.h"

#include <vector>

class WarningChecker {
private:
    std::vector<Warning*> warnings;

    void checkUnusedVariable(CodeGenVisitor & codeGenVisitor);

public:
    WarningChecker() {}
    ~WarningChecker();

    inline void AddWarning(Warning* warning) {
        warnings.push_back(warning);
    }
    inline void LogWarnings() {
        if (warnings.size() > 0) {
            for (Warning* warning : warnings) {
                warning->Log();
            }
        }
    }

    inline void CheckForWarnings(CodeGenVisitor & codeGenVisitor) {
        // check for unused variables
        checkUnusedVariable(codeGenVisitor);
    }
};
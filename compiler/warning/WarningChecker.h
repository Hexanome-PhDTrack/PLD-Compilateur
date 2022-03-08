#pragma once

#include "warning/Warning.h"
#include "warning/UnusedVariableWarning.h"
#include "CodeGenVisitor.h"

#include <vector>

class WarningChecker {
private:
    std::vector<Warning*> warnings;
    CodeGenVisitor & codeGenVisitor;

    void checkUnusedVariable() {
        for (auto & varData : codeGenVisitor.getMapVariables()) {
            if (!varData.second.IsUsed()) {
                warnings.push_back(new UnusedVariableWarning(varData.second));
            }
        }
    }

public:
    WarningChecker(
        CodeGenVisitor & codeGenVisitor
    ): codeGenVisitor(codeGenVisitor) {

    }
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

    inline void CheckForWarnings() {
        // check for unused variables
        checkUnusedVariable();
    }
};
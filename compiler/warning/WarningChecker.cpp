#include "WarningChecker.h"

void WarningChecker::checkUnusedVariable(
    CodeGenVisitor & codeGenVisitor
) {
    for (auto & varData : codeGenVisitor.getMapVariables()) {
        if (!varData.second.IsUsed()) {
            warnings.push_back(new UnusedVariableWarning(varData.second));
        }
    }
}

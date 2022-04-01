#include "warning/WarningManager.h"

WarningManager::~WarningManager() {
    if (warnings.size() > 0) {
        for (Warning* warning : warnings) {
            delete warning;
        }
    }
}

void WarningManager::LogWarnings() {
    if (warnings.size() > 0) {
        for (Warning* warning : warnings) {
            warning->Log();
        }
    }
}

void WarningManager::checkUnusedVariable(
    IntermediateRepresentation & ir
) {
    for(Function * f : ir.getAllFunctions()){
        VariableManager varManager = (f->getControlFlowGraph())->getVariableManager();
        std::vector<VarData> vars = varManager.getNoTempVariables();
        for (VarData var : vars) {
            if (!var.IsUsed()) {
                AddWarning(new UnusedVariableWarning(var));
            }
        }
    }
}
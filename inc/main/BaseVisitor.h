//
// Created by Mathieu Saugier on 15/03/2022.
//

#ifndef PLD_COMPILATEUR_BASEVISITOR_H
#define PLD_COMPILATEUR_BASEVISITOR_H

#include "./generated/ifccBaseVisitor.h"
#include "error/ErrorManager.h"
#include "warning/WarningManager.h"


class BaseVisitor : public ifccBaseVisitor
{
public:
    BaseVisitor() { }
    void throwError(CustomError *  error) { errorManager.AddError(error); throw error; }
    void throwWarning(Warning *warning) {warningManager.AddWarning(warning);}
    ErrorManager getErrorManager() { return errorManager; }
    WarningManager getWarningManager(){return warningManager;}

protected:
    ErrorManager errorManager;
    WarningManager warningManager;
    IntermediateRepresentation IR;

    // indicator of the advancement in exploration
    Function* currentFunction;
};

#endif //PLD_COMPILATEUR_BASEVISITOR_H

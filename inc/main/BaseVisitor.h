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
    BaseVisitor() { this->errorManager = new ErrorManager();
        this->warningManager = new WarningManager();
    }
    void throwError(Error *error) { errorManager->AddError(error); }
    void throwWarning(Warning *warning) {warningManager->AddWarning(warning);}
    ErrorManager *getErrorManager() { return errorManager; }
    WarningManager *getWarningManager(){return warningManager;}

protected:
    ErrorManager *errorManager;
    WarningManager *warningManager;
};

#endif //PLD_COMPILATEUR_BASEVISITOR_H

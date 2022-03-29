//
// Created by Mathieu Saugier on 15/03/2022.
//

#ifndef PLD_COMPILATEUR_BASEVISITOR_H
#define PLD_COMPILATEUR_BASEVISITOR_H

#include "./generated/ifccBaseVisitor.h"
#include "error/ErrorManager.h"
#include "warning/WarningManager.h"
#include "ir/block/Block.h"
#include "ir/flow/Function.h"
//instr
#include "ir/instruction/CopyInstr.h"
#include "ir/instruction/LdconstInstr.h"
#include "ir/instruction/AddInstr.h"
#include "ir/instruction/SubInstr.h"
#include "ir/instruction/MulInstr.h"
#include "ir/instruction/BitAndInstr.h"
#include "ir/instruction/BitOrInstr.h"
#include "ir/instruction/BitXor.h"
#include "ir/instruction/CmpGeInstr.h"
#include "ir/instruction/CmpGtInstr.h"
#include "ir/instruction/CmpNeqInstr.h"
#include "ir/instruction/NegInstr.h"
#include "ir/instruction/CmpLeInstr.h"
#include "ir/instruction/CmpLtInstr.h"
#include "ir/instruction/CmpEqInstr.h"
#include "ir/instruction/DivInstr.h"


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
    Block* currentBlock;
};

#endif //PLD_COMPILATEUR_BASEVISITOR_H

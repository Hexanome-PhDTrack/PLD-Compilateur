#pragma once

#include "./generated/ifccBaseVisitor.h"
#include "error/ErrorManager.h"
#include "warning/WarningManager.h"
#include "ir/block/Block.h"
#include "ir/flow/Function.h"

#include "ir/instruction/TypeIRInstr.h"
//instr
#include "ir/instruction/CopyInstr.h"
#include "ir/instruction/LdconstInstr.h"
#include "ir/instruction/AddInstr.h"
#include "ir/instruction/SubInstr.h"
#include "ir/instruction/MulInstr.h"
#include "ir/instruction/BitAndInstr.h"
#include "ir/instruction/BitOrInstr.h"
#include "ir/instruction/BitXorInstr.h"
#include "ir/instruction/CmpGeInstr.h"
#include "ir/instruction/CmpGtInstr.h"
#include "ir/instruction/CmpNeqInstr.h"
#include "ir/instruction/NegInstr.h"
#include "ir/instruction/CmpLeInstr.h"
#include "ir/instruction/CmpLtInstr.h"
#include "ir/instruction/CmpEqInstr.h"
#include "ir/instruction/DivInstr.h"
#include "ir/instruction/ReturnInstr.h"
#include "ir/instruction/CastCharToIntInstr.h"
#include "ir/instruction/CastIntToCharInstr.h"
#include "ir/instruction/CallInstr.h"
#include "ir/instruction/MoveFunctionArgInstr.h"
#include "ir/instruction/MoveFunctionParamInstr.h"
#include "ir/instruction/MoveFunctionReturnedValueInstr.h"
#include "ir/instruction/AddToRSPInstr.h"
#include "ir/instruction/SubToRSPInstr.h"
#include "ir/instruction/ControlStructInstr.h"
#include "ir/instruction/BitLeftShiftInstr.h"
#include "ir/instruction/BitRightShiftInstr.h"
#include "ir/instruction/BitComplementInstr.h"

class BaseVisitor : public ifccBaseVisitor
{
public:
    BaseVisitor() { currentBlock = nullptr;}
    void throwError(CustomError *  error) { errorManager.AddError(error); throw error; }
    void throwWarning(Warning *warning) {warningManager.AddWarning(warning);}
    IntermediateRepresentation& getIntermediateRepresentation(){return IR;};
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

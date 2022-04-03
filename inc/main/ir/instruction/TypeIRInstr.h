#pragma once

#include <string>

/*
In order to follow the type of the IRInstr when debugging with GDB,
one can use an enum of the IRInstr type.

NOTE: Please, add a new entry for each new IRInstr type you add.

WARN: IRInstr should not be added, base type
WARN: TypeIRInstr should not be added, enum
*/
enum TypeIRInstr {
    IR_AddInstr,
    IR_AddToRSPInstr,
    IR_BitAndInstr,
    IR_BitOrInstr,
    IR_BitXorInstr,
    IR_CallInstr,
    IR_CastCharToIntInstr,
    IR_CastIntToCharInstr,
    IR_CmpEqInstr,
    IR_CmpGeInstr,
    IR_CmpGtInstr,
    IR_CmpLeInstr,
    IR_CmpLtInstr,
    IR_CmpNeqInstr,
    IR_CopyInstr,
    IR_DivInstr,
    IR_LdconstInstr,
    IR_MoveFunctionArgInstr,
    IR_MoveFunctionParamInstr,
    IR_MulInstr,
    IR_NegInstr,
    IR_ReturnInstr,
    IR_RmemInstr,
    IR_SubInstr,
    IR_SubToRSPInstr,
    IR_WmemInstr
};
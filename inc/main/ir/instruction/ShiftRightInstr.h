#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

class ShiftRightInstr : public IRInstr {
   public:
    /**
     * @brief Construct a new Shift Right Instr object
     *
     * @param bb
     * @param t
     * @param params
     * var1 = var2 >> var3; => first parameter -> var1 | second parameter ->
     * var2 | third parameter -> var3
     */
    ShiftRightInstr(Block *bb, TypeName t, std::vector<VarData> params)
        : IRInstr(bb, t, params){};

    /** Actual code generation */
    virtual void gen_asm(std::ostream &o);
};

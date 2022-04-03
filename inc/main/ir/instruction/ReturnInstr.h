#pragma once

#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h"
#include "variable/TypeName.h"

#include <vector>
#include <string>
#include <iostream>

class ReturnInstr : public IRInstr
{
private:
    bool isVoidReturn = false;

public:
    /**
     * @brief Construct a new Mul Instr object
     *
     * @param bb
     * @param params
     * 
     * return var1 -> first paramater : var1
     */
    ReturnInstr(
        Block *bb, 
        std::vector<VarData> params
    ) : IRInstr(bb, IR_ReturnInstr, params) {};

    ReturnInstr(
        Block *bb, 
        bool isVoidReturn
    ) {
        this->bb = bb;
        this->isVoidReturn = isVoidReturn;
        this->t = IR_ReturnInstr;
    };

    virtual void gen_asm(std::ostream &o);
};
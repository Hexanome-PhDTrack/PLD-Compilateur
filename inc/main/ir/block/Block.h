#pragma once

#include "variable/TypeName.h"
#include "ir/flow/Function.h"

//#include "ir/instruction/IRInstr.h"
class IRInstr; // circular import
class ControlFlowGraph;

/*{
    public: 
        Function * GetFunction();
}*/

#include <vector>
#include <string>
#include <iostream>

//class Context;

class Block {
protected:
    std::string label; /**< label of the BB, also will be the label in the generated code. */
    std::vector<IRInstr *> instrs; /**< the instructions themselves. */
    ControlFlowGraph *cfg; /**< pointer to the CFG this block belongs to. */
    Block *exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure. */
    Block *exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump. */

    //Context *context;

public:

    Block(ControlFlowGraph *cfg, std::string entry_label/*, Context *ctx*/);

    ~Block();

    void gen_asm(std::ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

    void SetBlockLabel(std::string label) { this->label = label; }

    void AddIRInstr(IRInstr *instruction);

    // Getters
    Block *getExitTrue() {
        return exit_true;
    }

    Block *getExitFalse() {
        return exit_false;
    }

    std::string getBlockLabel() {
        return label;
    }

    /*Context *getContext() {
        return context;
    }*/

    std::vector<IRInstr *> getInstrs() {
        return instrs;
    }

    //Setters

    void setExitTrue(Block *b) {
        exit_true = b;
    }

    void setExitFalse(Block *b) {
        exit_false = b;
    }
};
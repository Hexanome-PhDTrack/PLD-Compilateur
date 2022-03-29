#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h" // circular import

Block::Block(ControlFlowGraph *cfg, BlockLabel entry_label/*, Context *ctx*/)
{
    exit_true = nullptr;
    exit_false = nullptr;
    this->cfg = cfg;
    //this->context = ctx;
    label = entry_label;
}

Block::~Block() {
    for(int i = 0; i < instrs.size(); i++){
        delete instrs[i];
    }
}

void Block::AddIRInstr(IRInstr * instruction) {
    instrs.push_back(instruction);
}
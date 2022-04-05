#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h" // circular import

Block::Block(ControlFlowGraph *cfg, BlockLabel entry_label/*, Context *ctx*/) {
    exit_true = nullptr;
    exit_false = nullptr;
    this->cfg = cfg;
    //this->context = ctx;
    label = entry_label;
}

Block::~Block() {
    for (int i = 0; i < (int)instrs.size(); i++) {
        delete instrs[i];
    }
}

void Block::AddIRInstr(IRInstr *instruction) {
    this->instrs.push_back(instruction);
}

void Block::gen_asm(std::ostream &o) {

    for (std::vector<IRInstr *>::iterator it = instrs.begin(); it != instrs.end(); it++) {
        (*it)->gen_asm(o);
    }
//    if (this->exit_true == nullptr) {
//        //we generate epilog after this function returns inside the cfg.
//        return;
//    } else {
//        if (this->exit_false == nullptr) {
////            o << "   jmp   " << exit_true->getBlockLabel() << "\n";
//        } else {
//            this->cfg->IR_reg_to_asm()
//        }
//    }

}
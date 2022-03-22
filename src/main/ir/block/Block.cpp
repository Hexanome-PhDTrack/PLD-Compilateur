#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h" // circular import

Block::~Block() {
    for(int i = 0; i < instrs.size(); i++){
        delete instrs[i];
    }
}

void Block::AddIRInstr(IRInstr * instruction) {
    instrs.push_back(instruction);
}
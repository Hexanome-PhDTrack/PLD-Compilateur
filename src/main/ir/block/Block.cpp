#include "ir/block/Block.h"

Block::~Block() {
    for(int i = 0; i < instrs.size(); i++){
        delete instrs[i];
    }
}

void Block::AddIRInstr(IRInstr * instruction) {
    instrs.push_back(instruction);
}
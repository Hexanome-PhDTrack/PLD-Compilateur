#include "ir/block/BlockManager.h"

BlockManager::BlockManager() {

}

BlockManager::~BlockManager() {
    for (int i = 0; i < (int)blocks.size(); i++) {
        delete blocks[i];
    }
}

void BlockManager::AddBlock(Block *block) {
    blocks.push_back(block);
}

void BlockManager::gen_asm(std::ostream &o) {
    for (int i = 0; i < (int)blocks.size(); ++i) {
        blocks[i]->gen_asm(o);
    }
}

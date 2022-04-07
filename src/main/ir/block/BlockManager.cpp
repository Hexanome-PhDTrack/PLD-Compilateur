#include "ir/block/BlockManager.h"

BlockManager::BlockManager() {

}

BlockManager::~BlockManager() {
    for (auto block : blocks) {
        delete block;
    }
}

void BlockManager::AddBlock(Block *block) {
    blocks.push_back(block);
}

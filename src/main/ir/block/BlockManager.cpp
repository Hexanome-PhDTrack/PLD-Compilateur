#include "ir/block/BlockManager.h"

BlockManager::BlockManager() {
    
}

BlockManager::~BlockManager() {
    for(int i = 0; i < blocks.size(); i++){
        delete blocks[i];
    }
}

void BlockManager::AddBlock(Block* block) {
    blocks.push_back(block);
}
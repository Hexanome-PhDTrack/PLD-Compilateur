#include "ir/block/BlockManager.h"

BlockManager::~BlockManager() {
    for(int i = 0; i < blocks.size(); i++){
        delete blocks[i];
    }
}
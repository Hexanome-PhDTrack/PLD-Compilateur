#pragma once

#include "ir/block/Block.h"

class BlockManager{
public:
    BlockManager();
    ~BlockManager();
    void addBlock(Block* block);
    void removeBlock(Block* block);
    void removeBlock(int index);
    void removeBlock(std::string name);
    Block* getBlock(int index);
    Block* getBlock(std::string name);
    int getBlockCount();
    void clear();

private:
    std::vector<Block*> blocks;
};
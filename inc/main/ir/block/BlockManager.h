#pragma once

#include "ir/block/Block.h"

class BlockManager{
public:
    BlockManager();
    ~BlockManager();
    void AddBlock(Block* block);
    void RemoveBlock(Block* block);
    void RemoveBlock(int index);
    void RemoveBlock(std::string name);
    Block* GetBlock(int index);
    Block* GetBlock(std::string name);
    int GetBlockCount();
    void Clear();

private:
    std::vector<Block*> blocks;
};
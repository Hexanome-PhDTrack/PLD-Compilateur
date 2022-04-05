#pragma once

#include "ir/block/Block.h"

class Block; // circular dependency

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
    std::vector<Block*> getBlocks(){
        return blocks;
    };

private:
    std::vector<Block*> blocks;
};
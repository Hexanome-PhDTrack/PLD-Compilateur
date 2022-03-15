#pragma once

#include "ir/block/Block.h"
#include "ir/flow/Function.h"

class CallData {
private:
    Function * caller; // calling function
    Function * callee; // called function
    Block * callBlock; // block where the call is made
    int callIndex; // index of the call instruction in the callBlock
    
public:
    CallData(
        Function * caller, 
        Function * callee, 
        Block * callBlock, 
        int callIndex
    ):
        caller(caller), 
        callee(callee), 
        callBlock(callBlock), 
        callIndex(callIndex) 
    {}
    ~CallData();
};
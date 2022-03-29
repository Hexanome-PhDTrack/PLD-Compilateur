#include "ir/flow/ControlFlowGraph.h"

ControlFlowGraph::ControlFlowGraph()
{
}

ControlFlowGraph::~ControlFlowGraph()
{
}

void ControlFlowGraph::AddBlock(Block *bb)
{
    this->blockManager.AddBlock(bb);
}

void ControlFlowGraph::gen_asm(std::ostream &o)
{
    // TODO
}

std::string ControlFlowGraph::IR_reg_to_asm(std::string name)
{
    VarData var = this->variableManager.getVariable(name);
    int index = var.GetIndex();
    std::string asm_result = index + "(%rbp)";
    return asm_result;
}

void ControlFlowGraph::gen_asm_prologue(std::ostream &o)
{
    // TODO
}

void ControlFlowGraph::gen_asm_epilogue(std::ostream &o)
{
    // TODO
}

std::string ControlFlowGraph::new_BB_name()
{
    // TODO
}
#include "ir/flow/ControlFlowGraph.h"

ControlFlowGraph::ControlFlowGraph()
{
}

ControlFlowGraph::~ControlFlowGraph()
{
    for (int i = 0; i < this->blocks.size(); i++)
    {
        delete this->blocks[i];
    }
}

void ControlFlowGraph::add_bb(Block *bb)
{
    this->blocks.push_back(bb);
}

void ControlFlowGraph::gen_asm(std::ostream &o)
{
    // TODO
}

std::string ControlFlowGraph::IR_reg_to_asm(std::string reg)
{
    VarData var = this->variableManager.getVariable(reg);
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
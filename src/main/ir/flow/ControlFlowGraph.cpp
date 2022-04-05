#include "ir/flow/ControlFlowGraph.h"
#include "ir/flow/Function.h" // circular dependency
#include "ir/block/Block.h" // circular dependency
#include "ir/block/BlockManager.h" // circular dependency

ControlFlowGraph::ControlFlowGraph(Function * function)
{
    this->variableManager = new VariableManager();
	this->blockManager = new BlockManager();
	this->nextBBnumber = 0;
	this->function = function;
}

ControlFlowGraph::~ControlFlowGraph()
{
    delete variableManager;
	delete blockManager;
}

Block * ControlFlowGraph::AddBlock()
{
	Block* block = new Block( // on crée un nouveau block
		this,
		this->new_BB_name()
	);
	if(blockManager->getBlocks().size()==0){
		this->firstBlock=block;
	}
	this->blockManager->AddBlock(block);
	return block;
}

void ControlFlowGraph::gen_asm(std::ostream &o)
{
   std::vector<Block*> blocks = blockManager->getBlocks();
   for(auto block : blocks){
	   block->gen_asm(o);
   }
}

std::string ControlFlowGraph::IR_reg_to_asm(std::string name, std::string scope)
{
    VarData var = this->variableManager->getVariable(name,scope);
    int index = var.GetIndex();
    std::string asm_result = index + "(%rbp)";
    return asm_result;
}

VariableManager * ControlFlowGraph::getVariableManager(){
    return variableManager;
}

VarData ControlFlowGraph::add_to_symbol_table(std::string name, size_t lineNumber, TypeName t, std::string scope){
    return variableManager->addVariable(name, lineNumber, t,scope);
}

VarData ControlFlowGraph::add_const_to_symbol_table(std::string name, size_t lineNumber, TypeName t, int value, std::string scope){
    return variableManager->addConst(name,lineNumber,t,value,scope);
}

VarData ControlFlowGraph::getVariable(std::string name, std::string scope){
    return variableManager->getVariable(name,scope);
}

bool ControlFlowGraph::isExist(std::string name, std::string scope){
    return variableManager->checkVarExists(name,scope);
}

TypeName ControlFlowGraph::get_var_type(std::string name, std::string scope){
    return variableManager->getVariable(name,scope).GetTypeName();
}

bool ControlFlowGraph::removeTempVariable(VarData var){
    return variableManager->removeTempVariable(var);
}

std::string ControlFlowGraph::new_BB_name()
{
	std::string returnValue = "L_" 
		+ std::to_string(nextBBnumber)
		+ function->GetName();
	nextBBnumber++;
	return returnValue;
}
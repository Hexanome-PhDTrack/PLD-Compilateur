#include "ir/flow/ControlFlowGraph.h"

ControlFlowGraph::ControlFlowGraph()
{
	this->nextBBnumber=0;
}

ControlFlowGraph::~ControlFlowGraph()
{
}

Block * ControlFlowGraph::AddBlock()
{
	Block* block = new Block( // on crée un nouveau block
		this,
		this->new_BB_name()
	);
	if(blockManager.getBlocks().size()==0){
		this->firstBlock=block;
	}
	this->blockManager.AddBlock(block);
	return block;
}

void ControlFlowGraph::gen_asm(std::ostream &o)
{
   std::vector<Block*> blocks = blockManager.getBlocks();
   for(auto block : blocks){
	   block->gen_asm(o);
   }
}

std::string ControlFlowGraph::IR_reg_to_asm(std::string name)
{
	VarData var = this->variableManager.getVariable(name);
	int index = var.GetIndex();
	std::string asm_result = index + "(%rbp)";
	return asm_result;
}

VariableManager ControlFlowGraph::getVariableManager(){
	return variableManager;
}

std::string ControlFlowGraph::new_BB_name()
{
	std::string returnValue = "L" + std::to_string(nextBBnumber);
	nextBBnumber++;
	return returnValue;
}

VarData ControlFlowGraph::add_to_symbol_table(std::string name, size_t lineNumber, TypeName t){
	return variableManager.addVariable(name, lineNumber, t);
}

VarData ControlFlowGraph::add_const_to_symbol_table(std::string name, size_t lineNumber, TypeName t, int value){
	return variableManager.addConst(name,lineNumber,t,value);
}

VarData ControlFlowGraph::getVariable(std::string name){
	return variableManager.getVariable(name);
}

bool ControlFlowGraph::isExist(std::string name){
	return variableManager.checkVarExists(name);
}

TypeName ControlFlowGraph::get_var_type(std::string name){
	return variableManager.getVariable(name).GetTypeName();
}

bool ControlFlowGraph::removeTempVariable(VarData var){
	return variableManager.removeTempVariable(var);
}
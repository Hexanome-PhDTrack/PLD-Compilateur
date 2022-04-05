#include "ir/block/Block.h"
#include "ir/instruction/IRInstr.h" // circular import

Block::Block(ControlFlowGraph *cfg, std::string entry_label/*, Context *ctx*/) {
	exit_true = nullptr;
	exit_false = nullptr;
	this->cfg = cfg;
	//this->context = ctx;
	label = entry_label;
}

Block::~Block() {
	for (int i = 0; i < (int)instrs.size(); i++) {
		delete instrs[i];
	}
}

void Block::AddIRInstr(IRInstr *instruction) {
	this->instrs.push_back(instruction);
}

void Block::gen_asm(std::ostream &o) {

	o << "." << getBlockLabel() << ":\n";

	for (auto instr : instrs) {
		instr->gen_asm(o);
	}
	if (this->exit_true == nullptr) {
		o << "	jmp .end\n";// on est a la fin
	}else{
		if (this->exit_false != nullptr) {
			o << "	je ." << exit_false->getBlockLabel() << "\n";
		}
		o << "	jmp ." << exit_true->getBlockLabel() << "\n";// on saute quoi u'il arrive
	}
}
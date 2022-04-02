#include "ir/flow/Function.h"

Function::Function(
    std::string name, TypeName returnType
) : name(name), returnType(returnType) {
    cfg = new ControlFlowGraph();
};

Function::~Function() {
    delete cfg;
};

std::string Function::GetName(){
    return name;
}

ControlFlowGraph * Function::getControlFlowGraph() {
    return cfg;
}

TypeName Function::getReturnType(){
    return returnType;
}

void Function::gen_asm(std::ostream &o)
{
    this->gen_asm_prologue(o);
    this->cfg->gen_asm(o);
    this->gen_asm_epilogue(o);
}

void Function::gen_asm_prologue(std::ostream &o)
{
    o << ".globl "<< name <<"\n";
    o << name <<":\n";
    o << 
    "    # prologue\n"
    "    pushq %rbp # save %rbp on the stack\n"
    "    movq %rsp, %rbp # define %rbp for the current function\n";

    // determine the size of the stack frame
    int stackFrameByteSize = cfg->getVariableManager().GetStackFrameByteSize();

    // compute upper closest power of 16 (alignment) to nb of pushed params to stack
    int nbToSubToRSP = 0;
    if (stackFrameByteSize % 16 != 0) {
        // compute next power of 16
        nbToSubToRSP = 16*(stackFrameByteSize/16 + 1);
    }

    // substract the size of the stack frame from the stack pointer
    if (nbToSubToRSP > 0) {
        o << "\tsubq $" << nbToSubToRSP << ", %rsp\n";
    }
}

void Function::gen_asm_epilogue(std::ostream &o)
{
    o << 
    "    # epilogue\n"
    "    leave # restore %rbp from the stack\n"
    "    ret # return to the caller (here the shell)\n";
}
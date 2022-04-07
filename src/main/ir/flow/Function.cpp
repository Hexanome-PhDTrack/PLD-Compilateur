#include "ir/flow/Function.h"

Function::Function(
    std::string name, TypeName returnType
) : name(name), returnType(returnType) {
    cfg = new ControlFlowGraph(this);
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
    // do not generate code for putchar and getchar
    if (name == "putchar" || name == "getchar") {
        return;
    }

    // generate code for special functions
    if (name == "vsum") {
        gen_asm_vsum(o);
        return;
    }

    this->gen_asm_prologue(o);
    this->cfg->gen_asm(o);
    this->gen_asm_epilogue(o);
}

void Function::gen_asm_prologue(std::ostream &o)
{
#ifdef __APPLE__
    if(name=="main") name="_main";
#endif
    o << ".globl "<< name <<"\n";
    o << name <<":\n";
    o << 
    "    # prologue\n"
    "    pushq %rbp # save %rbp on the stack\n"
    "    movq %rsp, %rbp # define %rbp for the current function\n";

    // determine the size of the stack frame
    int stackFrameByteSize = cfg->getVariableManager()->GetStackFrameByteSize();

    // compute upper closest power of 16 (alignment) to nb of pushed params to stack
    int nbToSubToRSP = 0;
    if (stackFrameByteSize % 16 != 0) {
        // compute next power of 16
        nbToSubToRSP = 16*(stackFrameByteSize/16 + 1);
    } else {
        nbToSubToRSP = stackFrameByteSize;
    }

    // substract the size of the stack frame from the stack pointer
    if (nbToSubToRSP > 0) {
        o << "\tsubq $" << nbToSubToRSP << ", %rsp\n";
    }
}

void Function::gen_asm_epilogue(std::ostream &o)
{
    o << "\t# epilogue\n";
    o << ".end_" << GetName() <<":\n";
    o << "\tleave # restore %rbp from the stack\n"
        "\tret # return to the caller (here the shell)\n";
}

VarData Function::AddArgument(
    std::string arg, 
    size_t lineNumber, 
    TypeName type
) {
    argumentNames.push_back(arg);
    return cfg->getVariableManager()->addVariable(arg, lineNumber, type);
}

VarData Function::GetArgument(std::string arg)
{
    return cfg->getVariableManager()->getVariable(arg);
}

size_t Function::GetArgumentIndex(std::string arg)
{
    for (size_t i = 0; i < argumentNames.size(); i++) {
        if (argumentNames.at(i) == arg) {
            return i;
        }
    }
    return -1;
}

std::vector<std::string> Function::GetArgumentNames()
{
    return argumentNames;
}

std::vector<std::pair<std::string, VarData>> Function::GetArguments()
{
    std::vector<std::pair<std::string, VarData>> args;
    for (std::string arg : argumentNames) {
        std::pair<std::string, VarData> argPair(
            arg, 
            cfg->getVariableManager()->getVariable(arg)
        );
        args.push_back(argPair);
    }
    return args;
}


// specialized functions
void Function::gen_asm_vsum(std::ostream &o)
{
    std::vector<std::string> lines;

    // read file line by line and store in lines
    std::ifstream file("res/vsum.s");
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // write lines to output
    for (std::string line : lines) {
        o << line << "\n";
    }
}
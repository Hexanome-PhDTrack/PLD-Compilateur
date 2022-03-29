#include "Visitor.h"

Visitor::Visitor() {

}

Visitor::~Visitor() {

}

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx) {
  return visit(ctx->prog());
}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
    for(auto func : ctx->func()){
        visit(func);
    }
    return 0;
}

antlrcpp::Any Visitor::visitFunc(ifccParser::FuncContext *ctx)
{
    currentFunction = new Function((ctx->VAR()[0])->getText(), TYPE_INT);
    IR.AddFunction(
        (ctx->VAR()[0])->getText(),
        currentFunction
    );
    return visit(ctx -> block());
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *ctx)
{
    ControlFlowGraph& cfg = currentFunction->getControlFlowGraph();
    Block* newBlock = new Block(
        BODY
    );
    cfg.AddBlock(newBlock);

    for(auto instr : ctx->instr()){
        visit(instr);
    }

    return 0;
}

antlrcpp::Any Visitor::visitInstr(ifccParser::InstrContext *ctx)
{

}

antlrcpp::Any Visitor::visitFuncReturn(ifccParser::FuncReturnContext *ctx)
{

}

antlrcpp::Any Visitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
    
}

antlrcpp::Any Visitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{
   
}

antlrcpp::Any Visitor::visitVarDefineMember(ifccParser::VarDefineMemberContext *ctx)
{
    
}

antlrcpp::Any Visitor::visitValue(ifccParser::ValueContext *ctx)
{
	

}

antlrcpp::Any Visitor::visitAddSub(ifccParser::AddSubContext *ctx)
{

}

antlrcpp::Any Visitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
	
}

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *ctx)
{
	
}
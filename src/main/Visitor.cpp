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
    ControlFlowGraph * cfg = currentFunction->getControlFlowGraph();
    Block* currentBlock = new Block(
        cfg,
        BODY
    );
    cfg->AddBlock(currentBlock);

    for(auto instr : ctx->instr()){
        visit(instr);
    }

    return 0;
}

antlrcpp::Any Visitor::visitInstr(ifccParser::InstrContext *ctx)
{
    return visit(ctx);
}

antlrcpp::Any Visitor::visitFuncReturn(ifccParser::FuncReturnContext *ctx)
{
    return visit(ctx);
}

antlrcpp::Any Visitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
    ControlFlowGraph * cfg = currentFunction->getControlFlowGraph();

    std::string varName = ctx->VAR()->getText();
    if(!cfg->isExist(varName)){
        VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT, false);
        throwError(new UndeclaredVariableError(toThrow));
    }
	VarData computedVariable = visit(ctx->expr());
	cfg->removeTempVariable(computedVariable);
	VarData leftVar = varManager.getVariable(ctx->VAR()->getText());

    std::vector<VarData> params;
    params.push_back(computedVariable);
    params.push_back(leftVar);

	currentBlock->AddIRInstr(new CopyInstr(currentBlock, TYPE_INT, params));
	return leftVar;
}

antlrcpp::Any Visitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{
   for(auto varCtx : ctx->varDefineMember())
    {
        visitVarDefineMember(varCtx);
    }

    return 0;
}

antlrcpp::Any Visitor::visitVarDefineMember(ifccParser::VarDefineMemberContext *ctx)
{
    ControlFlowGraph * cfg = currentFunction->getControlFlowGraph();
    std::string varName = ctx->VAR()->getText();
    //Check if the variable already exists, if yes we throw an error because it already exists.
    if(cfg->isExist(varName)){
		VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT, false);
        throwError(new UndeclaredVariableError(toThrow));
    }
    VarData newVar = cfg->add_to_symbol_table(ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);
    if(ctx->expr())
    {
        VarData computedVariable = visit(ctx->expr());
        cfg->removeTempVariable(computedVariable);
        std::vector<VarData> params;
        params.push_back(computedVariable);
        params.push_back(newVar);

        currentBlock->AddIRInstr(new CopyInstr(currentBlock, TYPE_INT, params));
    }

    return 0;
    
}

antlrcpp::Any Visitor::visitValue(ifccParser::ValueContext *ctx)
{
    ControlFlowGraph * cfg = currentFunction->getControlFlowGraph();
	// compute the tmp variable
	VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT); // variable temp to compute

	if (ctx->VAR())
	{
		if(cfg->isExist(ctx->VAR()->getText())){
			VarData varData = cfg->getVariable(ctx->VAR()->getText());

            std::vector<VarData> params;
            params.push_back(varData);
            params.push_back(newVar);

            currentBlock->AddIRInstr(new CopyInstr(currentBlock, TYPE_INT, params));
		}else{
			VarData toThrow = VarData(-1, ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT, false);

			throwError(new UndeclaredVariableError(toThrow));
		}
	}

	if (ctx->CONST())
	{
        VarData cst = cfg->add_const_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT, stoi(ctx->CONST()->getText()));
		// store cst to tmp
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(cst);
        currentBlock->AddIRInstr(new LdconstInstr(currentBlock, TYPE_INT, params));
	}

	return newVar;
}

antlrcpp::Any Visitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
    ControlFlowGraph * cfg = currentFunction->getControlFlowGraph();
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_ADD_SUB()->getText();
	VarData leftVar = visit(ctx->expr(0)).as<VarData>();
	VarData rightVar = visit(ctx->expr(1)).as<VarData>();

	cfg->removeTempVariable(leftVar);
	cfg->removeTempVariable(rightVar);

	if (operatorSymbol == "+")
	{
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(leftVar);
        params.push_back(rightVar);
        currentBlock->AddIRInstr(new AddInstr(currentBlock, TYPE_INT, params));
	}

	else if (operatorSymbol == "-")
	{
		std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(leftVar);
        params.push_back(rightVar);
        currentBlock->AddIRInstr(new SubInstr(currentBlock, TYPE_INT, params));
	}

	return newVar;
}

antlrcpp::Any Visitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
    ControlFlowGraph * cfg = currentFunction->getControlFlowGraph();
	VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_MUL_DIV()->getText();
	VarData leftVar = visit(ctx->expr(0)).as<VarData>();
	VarData rightVar = visit(ctx->expr(1)).as<VarData>();

	if(operatorSymbol == "/" && rightVar.IsConst() && rightVar.GetValue() == 0){
		warningManager.AddWarning(new DividingByZeroWarning(leftVar));
	}

	cfg->removeTempVariable(leftVar);
	cfg->removeTempVariable(rightVar);

	if (operatorSymbol == "*")
	{
		std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(leftVar);
        params.push_back(rightVar);
        currentBlock->AddIRInstr(new MulInstr(currentBlock, TYPE_INT, params));
	}

	else if (operatorSymbol == "/")
	{

	}

	return newVar;
}

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *ctx)
{
	return visit(ctx ->expr());
}
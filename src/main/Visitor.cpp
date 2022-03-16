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
	try{
		// USE TABS NOT SPACES YOU NERD
	#ifdef __APPLE__
		std::cout << ".globl _main\n"
					" _main: \n";
	#else
		std::cout << ".globl main\n"
					" main: \n";
	#endif
		std::cout << "	# prologue\n"
					"	pushq %rbp # save %rbp on the stack\n"
					"	movq %rsp, %rbp # define %rbp for the current function\n";

		for(auto expr : ctx->expr())
		{
			visit(expr);
		}

		VarData returnVar = visit(ctx->computedValue());
		std::cout << "	movl " << returnVar.GetIndex() << "(%rbp), %eax\n";

		std::cout << "	# epilogue\n"
					"	popq %rbp # restore %rbp from the stack\n"
					"	ret # return to the caller (here the shell)\n";
	}catch(const CustomError& e){
		// catch the error
	}
	// check and log warnings
	warningManager->CheckWarnings(varManager);
	warningManager->LogWarnings();

	// log errors
	errorManager->LogErrors();
    if(errorManager->hasErrors()) {return 1;}

    return 0;
}

antlrcpp::Any Visitor::visitExpr(ifccParser::ExprContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
    std::string varName = ctx->VAR()->getText();
    if(!varManager.checkVarExists(varName)){
        VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT);
        throwError(UndeclaredVariableError(toThrow));
    }
	VarData computedVariable = visit(ctx->computedValue());
	varManager.removeTempVariable(computedVariable);
	VarData leftVar = varManager.getVariable(ctx->VAR()->getText());

	std::cout << "	movl " << computedVariable.GetIndex() << "(%rbp), %eax\n"; // use eax => can't use movl on 2 stack pointer
	std::cout << "	movl %eax, " << leftVar.GetIndex() << "(%rbp)\n";
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
    std::string varName = ctx->VAR()->getText();
    //Check if the variable already exists, if yes we throw an error because it already exists.
    if(varManager.checkVarExists(varName)){
		VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT);
        throwError(UndeclaredVariableError(toThrow));
    }
    VarData newVar = varManager.addVariable(ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);
    if(ctx->computedValue())
    {
        VarData computedVariable = visit(ctx->computedValue());
        varManager.removeTempVariable(computedVariable);
        std::cout << "	movl " << computedVariable.GetIndex() << "(%rbp), %eax\n";
        std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
    }

    return 0;
}

antlrcpp::Any Visitor::visitValue(ifccParser::ValueContext *ctx)
{
	// compute the tmp variable
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT); // variable temp to compute

	if (ctx->VAR())
	{
		if(varManager.checkVarExists(ctx->VAR()->getText())){
			VarData varData = varManager.getVariable(ctx->VAR()->getText());

			// move var to tmp
			std::cout << "	movl " << varData.GetIndex() << "(%rbp), %eax\n";
			std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
		}else{
			VarData toThrow = VarData(-1, ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);

			throwError(UndeclaredVariableError(toThrow));
		}
	}

	if (ctx->CONST())
	{
		// store cst to tmp
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar;

}

antlrcpp::Any Visitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_ADD_SUB()->getText();
	VarData leftVar = visit(ctx->computedValue(0)).as<VarData>();
	VarData rightVar = visit(ctx->computedValue(1)).as<VarData>();

	varManager.removeTempVariable(leftVar);
	varManager.removeTempVariable(rightVar);

	// put left var in tmp
	std::cout << "	movl " << leftVar.GetIndex() << "(%rbp), %eax \n"; // get right var in eax

	if (operatorSymbol == "+")
	{
		std::cout << "	addl " << rightVar.GetIndex() << "(%rbp), %eax \n"; // add eax and right var in eax
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n"; // move eax in temp
	}

	else if (operatorSymbol == "-")
	{
		std::cout << "	subl " << rightVar.GetIndex() << "(%rbp), %eax\n"; // substract rightvar and eax (eax - rightvar) in eax
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n"; // move eax in tmp
	}

	return newVar;
}

antlrcpp::Any Visitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_MUL_DIV()->getText();
	VarData leftVar = visit(ctx->computedValue(0)).as<VarData>();
	VarData rightVar = visit(ctx->computedValue(1)).as<VarData>();

	varManager.removeTempVariable(leftVar);
	varManager.removeTempVariable(rightVar);

	std::cout << "	movl " << leftVar.GetIndex() << "(%rbp), %eax \n"; // get left var in eax

	if (operatorSymbol == "*")
	{
		std::cout << "	imull " << rightVar.GetIndex() << "(%rbp), %eax\n"; // mul eax and rightvar in eax
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	else if (operatorSymbol == "/")
	{
		// TODO: Ajouter vérification + warning si on divise par 0
		std::cout << "	cltd\n";
		std::cout << "	idivl " << rightVar.GetIndex() << "(%rbp)\n"; // divise eax by rightvar in eax
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar;
}

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *ctx)
{
	return visit(ctx ->computedValue());
}
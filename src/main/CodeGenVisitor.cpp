#include "CodeGenVisitor.h"

CodeGenVisitor::CodeGenVisitor() {

}

CodeGenVisitor::~CodeGenVisitor() {

}

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	// USE TABS NOT SPACES YOU NERD
#ifdef __APPLE__
	std::cout << ".globl _main\n"
				 " _main: \n";
#else
	std::cout << ".globl	main\n"
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

	// check and log warnings
	warningManager.CheckWarnings(varManager);
	warningManager.LogWarnings();

	// log errors
	errorManager.LogErrors();
	
    return returnVar;
}

antlrcpp::Any CodeGenVisitor::visitExpr(ifccParser::ExprContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
	VarData computedVariable = visit(ctx->computedValue());
	VarData leftVar = varManager.getVariable(ctx->VAR()->getText());

	std::cout << "	movl " << computedVariable.GetIndex() << "(%rbp), %eax\n"; // use eax => can't use movl on 2 stack pointer
	std::cout << "	movl %eax, " << leftVar.GetIndex() << "(%rbp)\n";
	return leftVar;
}

antlrcpp::Any CodeGenVisitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{
	VarData newVar = varManager.addVariable(ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);
	if(ctx->computedValue())
	{
		VarData computedVariable = visit(ctx->computedValue());
		std::cout << "	movl " << computedVariable.GetIndex() << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}
	
	return newVar;
}

antlrcpp::Any CodeGenVisitor::visitValue(ifccParser::ValueContext *ctx)
{
	if (ctx->VAR())
	{
		// return the variable
		return varManager.getVariable(ctx->VAR()->getText());
	}

	else //ctx->CONST() -> vrai
	{
		// compute a temp variable with the constante
		VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT); // variable temp to compute
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVar.GetIndex() << "(%rbp)\n"; // store the cst
		return newVar;
	}
}

antlrcpp::Any CodeGenVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_ADD_SUB()->getText();
	VarData leftVar = visit(ctx->computedValue(0)).as<VarData>();
	VarData rightVar = visit(ctx->computedValue(1)).as<VarData>();

	std::cout << "	movl " << leftVar.GetIndex() << "(%rbp), %eax\n"; // get left var in temp
	std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";

	std::cout << "	movl " << rightVar.GetIndex() << "(%rbp), %eax\n"; // get right var in eax

	if (operatorSymbol == "+")
	{
		std::cout << "	addl %eax, " << newVar.GetIndex() << "(%rbp)\n"; // add eax and temp in tmp

	}

	else if (operatorSymbol == "-")
	{
		// TODO : correct sub
		std::cout << "	subl %eax, " << newVar.GetIndex() << "(%rbp)\n"; // substract eax and temp in temp
	}

	return newVar;
}

antlrcpp::Any CodeGenVisitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_MUL_DIV()->getText();
	VarData leftVar = visit(ctx->computedValue(0)).as<VarData>();
	VarData rightVar = visit(ctx->computedValue(1)).as<VarData>();

	std::cout << "	movl " << leftVar.GetIndex() << "(%rbp), %eax\n"; // get left var in temp
	std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";

	std::cout << "	movl " << rightVar.GetIndex() << "(%rbp), %eax\n"; // get right var in eax

	if (operatorSymbol == "*")
	{
		std::cout << "	imull " << newVar.GetIndex() << "(%rbp), %eax\n"; // mul eax and temp in eax
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	else if (operatorSymbol == "/")
	{	
		std::cout << "	cltd\n";
		std::cout << "	idivl " << newVar.GetIndex() << "(%rbp)\n"; // divise temp by eax in eax
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar;
}
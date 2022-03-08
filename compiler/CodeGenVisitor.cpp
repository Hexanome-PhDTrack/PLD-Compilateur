#include "CodeGenVisitor.h"

VarData CodeGenVisitor::createVariable(std::string varName, std::string lineContext, size_t lineNumber, TypeName typeName)
{
	int newVarIndex = (-4) * (++currentVarIndex);
	VarData newVar = VarData(
		newVarIndex,
		varName,
		lineContext,
		lineNumber,
		TYPE_INT
	);

	// define variable data
	varData.insert(
		std::pair<std::string, VarData>(
			varName,
			newVar
		)
	);

	return newVar;
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

	int returnVarIndex = visit(ctx->computedValue());
	std::cout << "	movl " << returnVarIndex << "(%rbp), %eax\n";

	std::cout << "	# epilogue\n"
				 "	popq %rbp # restore %rbp from the stack\n"
				 "	ret # return to the caller (here the shell)\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitExpr(ifccParser::ExprContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
	int computedVariableIndex = visit(ctx->computedValue());
	VarData leftVar = varData.find(ctx->VAR()->getText())->second;

	std::cout << "	movl " << computedVariableIndex << "(%rbp), %eax\n";
	std::cout << "	movl %eax, " << leftVar.GetIndex() << "(%rbp)\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{

	VarData newVar = createVariable(ctx->VAR()->getText(), ctx->getText(), ctx->getStart()->getLine(), TYPE_INT);
	if(ctx->computedValue())
	{
		int computedVariableIndex = visit(ctx->computedValue());
		std::cout << "	movl " << computedVariableIndex << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitValue(ifccParser::ValueContext *ctx)
{
	std::string varName = "#tmp" + (currentVarIndex + 1);
	VarData newVar = createVariable(varName, ctx->getText(), ctx->getStart()->getLine(), TYPE_INT);

	if (ctx->VAR())
	{
		std::cout << "	movl " << varData.find(ctx->VAR()->getText())->second.GetIndex() << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	if (ctx->CONST())
	{
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar.GetIndex();
}

antlrcpp::Any CodeGenVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
	std::string varName = "#tmp" + (currentVarIndex + 1);
	VarData newVar = createVariable(varName, ctx->getText(), ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_ADD_SUB()->getText();
	int leftVarIndex = visit(ctx->computedValue(0));
	int rightVarIndex = visit(ctx->computedValue(1));

	std::cout << "	movl " << leftVarIndex << "(%rbp), %eax\n";
	std::cout << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	std::cout << "	movl " << rightVarIndex << "(%rbp), %eax\n";

	if (operatorSymbol == "+")
	{
		std::cout << "	addl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	else if (operatorSymbol == "-")
	{
		std::cout << "	subl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar.GetIndex();
}
#include "CodeGenVisitor.h"

CodeGenVisitor::CodeGenVisitor() {

}

CodeGenVisitor::~CodeGenVisitor() {
	if(targetStream != nullptr)
	{
		delete targetStream;
	}
}

void CodeGenVisitor::setTargetFileBuffer(std::streambuf *fileBuffer)
{
	if(targetStream != nullptr)
	{
		delete targetStream;
	}

	targetStream = new std::ostream(fileBuffer);
}

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	// USE TABS NOT SPACES YOU NERD
#ifdef __APPLE__
	*targetStream << ".globl _main\n"
				 " _main: \n";
#else
	*targetStream << ".globl	main\n"
				 " main: \n";
#endif
	*targetStream << "	# prologue\n"
				 "	pushq %rbp # save %rbp on the stack\n"
				 "	movq %rsp, %rbp # define %rbp for the current function\n";

	for(auto expr : ctx->expr())
	{
		visit(expr);
	}

	VarData returnVar = visit(ctx->computedValue());
	*targetStream << "	movl " << returnVar.GetIndex() << "(%rbp), %eax\n";

	*targetStream << "	# epilogue\n"
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
	varManager.removeTempVariable(computedVariable);
	VarData leftVar = varManager.getVariable(ctx->VAR()->getText());

	*targetStream << "	movl " << computedVariable.GetIndex() << "(%rbp), %eax\n"; // use eax => can't use movl on 2 stack pointer
	*targetStream << "	movl %eax, " << leftVar.GetIndex() << "(%rbp)\n";
	return leftVar;
}

antlrcpp::Any CodeGenVisitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{
	for(auto varCtx : ctx->varDefineMember())
	{
		visitVarDefineMember(varCtx);
	}
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDefineMember(ifccParser::VarDefineMemberContext *ctx)
{
	VarData newVar = varManager.addVariable(ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);
	if(ctx->computedValue())
	{
		VarData computedVariable = visit(ctx->computedValue());
		varManager.removeTempVariable(computedVariable);
		*targetStream << "	movl " << computedVariable.GetIndex() << "(%rbp), %eax\n";
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}
	
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitValue(ifccParser::ValueContext *ctx)
{
	// compute the tmp variable
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT); // variable temp to compute

	if (ctx->VAR())
	{
		// move var to tmp
		*targetStream << "	movl " << varManager.getVariable(ctx->VAR()->getText()).GetIndex() << "(%rbp), %eax\n";
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	if (ctx->CONST())
	{
		// store cst to tmp
		*targetStream << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar;

}

antlrcpp::Any CodeGenVisitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_ADD_SUB()->getText();
	VarData leftVar = visit(ctx->computedValue(0)).as<VarData>();
	VarData rightVar = visit(ctx->computedValue(1)).as<VarData>();

	varManager.removeTempVariable(leftVar);
	varManager.removeTempVariable(rightVar);

	// put left var in tmp
	*targetStream << "	movl " << leftVar.GetIndex() << "(%rbp), %eax \n"; // get right var in eax

	if (operatorSymbol == "+")
	{
		*targetStream << "	addl " << rightVar.GetIndex() << "(%rbp), %eax \n"; // add eax and right var in eax
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n"; // move eax in temp
	}

	else if (operatorSymbol == "-")
	{
		*targetStream << "	subl " << rightVar.GetIndex() << "(%rbp), %eax\n"; // substract rightvar and eax (eax - rightvar) in eax
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n"; // move eax in tmp
	}

	return newVar;
}

antlrcpp::Any CodeGenVisitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
	VarData newVar = varManager.addVariable("#tmp", ctx->getStart()->getLine(), TYPE_INT);
	
	std::string operatorSymbol = ctx->OP_MUL_DIV()->getText();
	VarData leftVar = visit(ctx->computedValue(0)).as<VarData>();
	VarData rightVar = visit(ctx->computedValue(1)).as<VarData>();

	varManager.removeTempVariable(leftVar);
	varManager.removeTempVariable(rightVar);

	*targetStream << "	movl " << leftVar.GetIndex() << "(%rbp), %eax \n"; // get left var in eax

	if (operatorSymbol == "*")
	{
		*targetStream << "	imull " << rightVar.GetIndex() << "(%rbp), %eax\n"; // mul eax and rightvar in eax
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	else if (operatorSymbol == "/")
	{	
		// TODO: Ajouter vérification + warning si on divise par 0
		*targetStream << "	cltd\n";
		*targetStream << "	idivl " << rightVar.GetIndex() << "(%rbp)\n"; // divise eax by rightvar in eax
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar;
}

antlrcpp::Any CodeGenVisitor::visitParenthesis(ifccParser::ParenthesisContext *ctx)
{
	return visit(ctx ->computedValue());
}
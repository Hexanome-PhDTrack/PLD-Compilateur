#include "CodeGenVisitor.h"

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	// USE TABS NOT SPACES YOU NERD
	std::cout<<
		".globl	main\n"
		" main: \n"
		"	# prologue\n"
		"	pushq %rbp # save %rbp on the stack\n"
		"	movq %rsp, %rbp # define %rbp for the current function\n";

		visitChildren(ctx);

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
	if(ctx->VAR(1)){
		std::cout << "	movl " << varIndexes.find(ctx->VAR(1)->getText())->second << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << varIndexes.find(ctx->VAR(0)->getText())->second << "(%rbp)\n";
	}
	else if(ctx->CONST()){
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << varIndexes.find(ctx->VAR(0)->getText())->second << "(%rbp)\n";
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{
	int newVarIndex = (-4)*(++currentVarIndex);
	varIndexes.insert(std::pair<std::string, int>(ctx->VAR(0)->getText(), newVarIndex));

	if(ctx->VAR(1)){
		std::cout << "	movl " << varIndexes.find(ctx->VAR(1)->getText())->second << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << newVarIndex << "(%rbp)\n";
	}
	else if(ctx->CONST()){
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVarIndex << "(%rbp)\n";
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitComputedValue2(ifccParser::ComputedValue2Context *ctx)
{
	
}
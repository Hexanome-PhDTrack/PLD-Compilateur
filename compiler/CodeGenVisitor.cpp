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

		if(ctx->CONST()){
			int retval = stoi(ctx->CONST()->getText());
			std::cout << "	movl $"<<retval<<", %eax\n";
		}
		else if(ctx->VAR()){
			std::cout << "	movl " << varIndexes.find(ctx->VAR()->getText())->second << "(%rbp), %eax\n";
		}

		std::cout << "	# epilogue\n"
		"	popq %rbp # restore %rbp from the stack\n"
		"	ret # return to the caller (here the shell)\n";

	return 0;
}

antlrcpp::Any CodeGenVisitor::visitConstAssign(ifccParser::ConstAssignContext *ctx)
{
	int newVarIndex = (-4)*(++currentVarIndex);
	varIndexes.insert(std::pair<std::string, int>(ctx->VAR()->getText(), newVarIndex));
	std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVarIndex << "(%rbp)\n";
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
	return 0;
}
#include "CodeGenVisitor.h"
#include "variable/TypeName.h"

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
			std::cout << "	movl " << varData.find(ctx->VAR()->getText())->second.index << "(%rbp), %eax\n";
		}

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
		std::cout << "	movl " << varData.find(ctx->VAR(1)->getText())->second.index << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << varData.find(ctx->VAR(0)->getText())->second.index << "(%rbp)\n";
	}
	else if(ctx->CONST()){
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << varData.find(ctx->VAR(0)->getText())->second.index << "(%rbp)\n";
	}
	return 0;
}

antlrcpp::Any CodeGenVisitor::visitVarDefine(ifccParser::VarDefineContext * ctx)
{
	int newVarIndex = (-4)*(++currentVarIndex);

	// define variable data

	// TODO: fix this
	size_t lineNumber = ctx->getStart()->getLine();
	std::string varName = ctx->VAR()->getText();
	std::string lineContext = ctx->getText();
	varData.insert(
		std::pair<std::string, VarData>(
			ctx->VAR(1)->getText(),
			VarData(
				newVarIndex,
				varName, 
				lineContext,
				lineNumber,
				TYPE_INT
			)
		)
	);

	//varData.insert(std::pair<std::string, int>(ctx->VAR(0)->getText(), newVarIndex));

	if(ctx->VAR(1)){
		std::cout << "	movl " << varData.find(ctx->VAR(1)->getText())->second.index << "(%rbp), %eax\n";
		std::cout << "	movl %eax, " << newVarIndex << "(%rbp)\n";
	}
	else if(ctx->CONST()){
		std::cout << "	movl $" << stoi(ctx->CONST()->getText()) << ", " << newVarIndex << "(%rbp)\n";
	}
	return 0;
}
#include "CodeGenVisitor.h"

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) 
{
	int retval = stoi(ctx->CONST()->getText());
	std::cout<<".globl	main\n"
		" main: \n"
		" 	movl	$"<<retval<<", %eax\n"
		" 	ret\n";

	return 0;
}


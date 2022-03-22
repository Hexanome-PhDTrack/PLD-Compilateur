#include "CodeGenVisitor.h"
#include "warning/DividingByZeroWarning.h"

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

antlrcpp::Any CodeGenVisitor::visitAxiom(ifccParser::AxiomContext *ctx) {
    return visit(ctx->prog());
}

antlrcpp::Any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	try{
		// USE TABS NOT SPACES YOU NERD
	#ifdef __APPLE__
		*targetStream << ".globl _main\n"
					" _main: \n";
	#else
		*targetStream << ".globl main\n"
					" main: \n";
	#endif
		*targetStream << "	# prologue\n"
					"	pushq %rbp # save %rbp on the stack\n"
					"	movq %rsp, %rbp # define %rbp for the current function\n";

        visitChildren(ctx);

		*targetStream << "	# epilogue\n"
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

antlrcpp::Any CodeGenVisitor::visitFunc(ifccParser::FuncContext *ctx)
{
    std::vector<antlr4::tree::TerminalNode *> types = ctx->TYPE();
    std::vector<antlr4::tree::TerminalNode *> names = ctx->VAR();
    std::string funcType = types[0]->getText();
    std::string funcName = names[0]->getText();

    //if(!varManager.checkVarExists(funcName)){
        //TODO add correct type
        //VarData toThrow = VarData(-1, funcName, ctx->getStart()->getLine(), TYPE_INT);
        //throwError(UndeclaredVariableError(toThrow));
    //}
    //VarData newVar = varManager.addVariable(funcName, ctx->getStart()->getLine(), TYPE_INT);
    visitChildren(ctx);
    return 0;

}

antlrcpp::Any CodeGenVisitor::visitBlock(ifccParser::BlockContext *ctx)
{
    for(auto instr : ctx->instr())
    {
        visit(instr);
    }
    return 0;

}

antlrcpp::Any CodeGenVisitor::visitInstr(ifccParser::InstrContext *ctx)
{
	return visitChildren(ctx);
}

antlrcpp::Any CodeGenVisitor::visitFuncReturn(ifccParser::FuncReturnContext *ctx)
{
    VarData returnVar = visit(ctx->expr());
    *targetStream << "	movl " << returnVar.GetIndex() << "(%rbp), %eax\n";
    return 0;

}
antlrcpp::Any CodeGenVisitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
    std::string varName = ctx->VAR()->getText();
    if(!varManager.checkVarExists(varName)){
        VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT);
        throwError(UndeclaredVariableError(toThrow));
    }
	VarData computedVariable = visit(ctx->expr());
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
    std::string varName = ctx->VAR()->getText();
    //Check if the variable already exists, if yes we throw an error because it already exists.
    if(varManager.checkVarExists(varName)){
		VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT);
        throwError(UndeclaredVariableError(toThrow));
    }
    VarData newVar = varManager.addVariable(ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);
    if(ctx->expr())
    {
        VarData computedVariable = visit(ctx->expr());
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
		if(varManager.checkVarExists(ctx->VAR()->getText())){
			VarData varData = varManager.getVariable(ctx->VAR()->getText());

			// move var to tmp
			*targetStream << "	movl " << varData.GetIndex() << "(%rbp), %eax\n";
			*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
		}else{
			VarData toThrow = VarData(-1, ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT);

			throwError(UndeclaredVariableError(toThrow));
		}
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
	VarData leftVar = visit(ctx->expr(0)).as<VarData>();
	VarData rightVar = visit(ctx->expr(1)).as<VarData>();

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
	VarData leftVar = visit(ctx->expr(0)).as<VarData>();
	VarData rightVar = visit(ctx->expr(1)).as<VarData>();

	if(operatorSymbol == "/" && ctx->expr(1)->getText() == "0"){
		warningManager->AddWarning(new DividingByZeroWarning(leftVar));
	}

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
		*targetStream << "	cltd\n";
		*targetStream << "	idivl " << rightVar.GetIndex() << "(%rbp)\n"; // divise eax by rightvar in eax
		*targetStream << "	movl %eax, " << newVar.GetIndex() << "(%rbp)\n";
	}

	return newVar;
}

antlrcpp::Any CodeGenVisitor::visitParenthesis(ifccParser::ParenthesisContext *ctx)
{
	return visit(ctx ->expr());
}
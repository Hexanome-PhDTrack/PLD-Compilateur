#include "Visitor.h"

Visitor::Visitor()
{
}

Visitor::~Visitor()
{
}

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
    try
    {
        visit(ctx->prog());
        warningManager.CheckWarnings(IR);
        warningManager.LogWarnings();
    }
    catch (CustomError *e)
    {
        errorManager.LogErrors();
        return 1;
    }
    return 0;
}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
    for (auto func : ctx->func())
    {
        visit(func);
    }
    return 0;
}

antlrcpp::Any Visitor::visitFunc(ifccParser::FuncContext *ctx)
{
    // create current function
    currentFunction = new Function((ctx->VAR()[0])->getText(), TYPE_INT);
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    Block *newBlock = cfg->AddBlock();

    currentBlock = newBlock; // reset the block

    IR.AddFunction(
        (ctx->VAR()[0])->getText(),
        currentFunction);

    for (size_t i = 1; i < ctx->VAR().size(); i++) // skip first VAR (function name)
    {
        // add function arguments, and associate them with local variables
        std::string varName = ctx->VAR()[i]->getText();
        size_t lineNumber = ctx->VAR()[i]->getSymbol()->getLine();
        TypeName varType = getTypeNameFromString(ctx->TYPE()[i]->getText());

        VarData argument = currentFunction->AddArgument(
            varName,
            lineNumber, // ctx->getStart()->getLine()
            varType);

        // get the register used to store the argument
        std::vector<std::string> registers = {"edi", "esi", "edx", "ecx", "r8d", "r9d"};
        size_t argIndex = currentFunction->GetArgumentIndex(varName);
        std::string fromRegister = argIndex < 6 ? registers[argIndex] : "";

        // add instructions to move arguments to local variables
        std::vector<VarData> params;
        params.push_back(argument);

        currentBlock->AddIRInstr(
            new MoveFunctionArgInstr(
                currentBlock,
                params,
                fromRegister, // only used when argument is passed in a register
                argIndex));
    }

    return visit(ctx->block());
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    int i = 0;
    for (auto instr : ctx->instr())
    {
        if (instr->block())
        { // si on rencontre un block, on doit continuer dans un nouveau block enchainé au block précédent
            Block *suite = cfg->AddBlock();
            currentBlock->setExitTrue(suite);
            currentBlock = suite;
        }
        // std::cout << "testI" << i << std::endl;
        visit(instr);
        // std::cout << "testI" << i << "fin"<< std::endl;
        //  if we have other instr, we recreate a block

        if (instr->block())
        {
            Block *suite = cfg->AddBlock();
            currentBlock->setExitTrue(suite);
            currentBlock = suite;
        }
        i++;
    }

    if (ctx->funcReturn())
    {
        return visit(ctx->funcReturn());
    }

    return 0;
}

antlrcpp::Any Visitor::visitInstr(ifccParser::InstrContext *ctx)
{

    return visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFuncReturn(ifccParser::FuncReturnContext *ctx)
{
    VarData computedVariable = visit(ctx->expr());
    std::vector<VarData> params;
    params.push_back(computedVariable);

    // check that the return type is the same as the function return type
    if (computedVariable.GetTypeName() != currentFunction->getReturnType())
    {
        throwWarning(new ReturnTypeWarning(*currentFunction));
    }

    // if function is void, force nop instruction
    ReturnInstr *instr;
    if (currentFunction->getReturnType() == TYPE_VOID)
    {
        instr = new ReturnInstr(
            currentBlock, true, currentFunction->GetName());
    }
    else
    {
        instr = new ReturnInstr(
            currentBlock, params, currentFunction->GetName());
    }
    currentBlock->AddIRInstr(instr);

    return computedVariable;
}

antlrcpp::Any Visitor::visitVarAssign(ifccParser::VarAssignContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();

    std::string varName = ctx->VAR()->getText();
    if (!cfg->isExist(varName))
    {
        VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT, false);
        UndeclaredVariableError *errorCustom = new UndeclaredVariableError(toThrow);
        throwError(errorCustom);
    }
    VarData computedVariable = visit(ctx->expr());
    cfg->removeTempVariable(computedVariable);
    VarData leftVar = cfg->getVariable(ctx->VAR()->getText());

    std::vector<VarData> params;
    params.push_back(leftVar);
    params.push_back(computedVariable);

    IRInstr *instr;
    TypeName leftVarType = leftVar.GetTypeName();
    switch (leftVarType)
    {
    case TYPE_CHAR:
        instr = new CastIntToCharInstr(currentBlock, params);
        break;

    case TYPE_INT:
    default:
        instr = new CopyInstr(currentBlock, params);
        break;
    }
    currentBlock->AddIRInstr(instr);
    return leftVar;
}

antlrcpp::Any Visitor::visitVarDefine(ifccParser::VarDefineContext *ctx)
{
    TypeName varType = getTypeNameFromString(ctx->TYPE()->getText());

    switch (varType)
    {
    case TYPE_INT:
    case TYPE_CHAR:
        for (auto varCtx : ctx->varDefineMember())
        {
            visitVarDefineMember(varCtx);
        }

        return 0;

    default:
        VarData toThrow = VarData(-1, "", ctx->getStart()->getLine(), varType, false);
        IllegalTypeError *errorCustom = new IllegalTypeError(toThrow);
        throwError(errorCustom);
        return 0;
    }
}

antlrcpp::Any Visitor::visitVarDefineMember(ifccParser::VarDefineMemberContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    std::string varName = ctx->VAR()->getText();

    // Check if the variable already exists, if yes we throw an error because it already exists.
    if (cfg->isExist(varName))
    {
        VarData toThrow = VarData(-1, varName, ctx->getStart()->getLine(), TYPE_INT, false);
        MultipleDeclarationError *errorCustom = new MultipleDeclarationError(toThrow);
        throwError(errorCustom);
    }

    ifccParser::VarDefineContext *varDefCtx = (ifccParser::VarDefineContext *)(ctx->parent);
    TypeName newVarType = getTypeNameFromString(varDefCtx->TYPE()->getText());
    // std::cout << "New variable of type " << varDefCtx->TYPE()->getText() << std::endl;
    VarData newVar = cfg->add_to_symbol_table(ctx->VAR()->getText(), ctx->getStart()->getLine(), newVarType);
    // std::cout << "TypeName: " << newVar.GetTypeName() << std::endl;
    if (ctx->expr())
    {
        VarData computedVariable = visit(ctx->expr());
        cfg->removeTempVariable(computedVariable);
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(computedVariable);

        IRInstr *instr;
        switch (newVarType)
        {
        case TYPE_CHAR:
            instr = new CastIntToCharInstr(currentBlock, params);
            break;

        case TYPE_INT:
        default:
            instr = new CopyInstr(currentBlock, params);
            break;
        }
        currentBlock->AddIRInstr(instr);
    }

    return newVar;
}

antlrcpp::Any Visitor::visitValue(ifccParser::ValueContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    // compute the tmp variable
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT); // variable temp to compute

    if (ctx->VAR())
    {
        if (cfg->isExist(ctx->VAR()->getText()))
        {
            VarData varData = cfg->getVariable(ctx->VAR()->getText());
            std::vector<VarData> params;
            params.push_back(newVar);
            params.push_back(varData);

            IRInstr *instr;
            TypeName varType = varData.GetTypeName();
            switch (varType)
            {
            case TYPE_CHAR:
                instr = new CastCharToIntInstr(currentBlock, params);
                break;

            case TYPE_INT:
            default:
                instr = new CopyInstr(currentBlock, params);
                break;
            }
            currentBlock->AddIRInstr(instr);
        }
        else
        {
            VarData toThrow = VarData(-1, ctx->VAR()->getText(), ctx->getStart()->getLine(), TYPE_INT, false);
            UndeclaredVariableError *errorCustom = new UndeclaredVariableError(toThrow);
            throwError(errorCustom);
        }
    }

    if (ctx->CONST())
    {
        std::string constValue = ctx->CONST()->getText();
        VarData cst = cfg->add_const_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT, stoi(constValue));
        // store cst to tmp
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(cst);
        LdconstInstr *instr = new LdconstInstr(currentBlock, params);
        currentBlock->AddIRInstr(instr);
    }

    if (ctx->CHAR())
    {
        int charText = ctx->CHAR()->getText()[1];
        std::vector<VarData> params;
        VarData intChar = cfg->add_const_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT, charText);
        params.push_back(newVar);
        params.push_back(intChar);
        LdconstInstr *instr = new LdconstInstr(currentBlock, params);
        currentBlock->AddIRInstr(instr);
    }
    return newVar;
}

antlrcpp::Any Visitor::visitAddSub(ifccParser::AddSubContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);

    std::string operatorSymbol = ctx->OP_ADD_SUB->getText();
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
        AddInstr *addInstr = new AddInstr(currentBlock, params);
        currentBlock->AddIRInstr(addInstr);
    }

    else if (operatorSymbol == "-")
    {
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(leftVar);
        params.push_back(rightVar);
        SubInstr *subInstr = new SubInstr(currentBlock, params);
        currentBlock->AddIRInstr(subInstr);
    }

    return newVar;
}

antlrcpp::Any Visitor::visitMulDiv(ifccParser::MulDivContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);

    std::string operatorSymbol = ctx->OP_MUL_DIV()->getText();
    VarData leftVar = visit(ctx->expr(0)).as<VarData>();
    VarData rightVar = visit(ctx->expr(1)).as<VarData>();

    if (operatorSymbol == "/" && rightVar.IsConst() && rightVar.GetValue() == 0)
    {
        DividingByZeroWarning *errorCustom = new DividingByZeroWarning(leftVar);
        warningManager.AddWarning(errorCustom);
    }

    cfg->removeTempVariable(leftVar);
    cfg->removeTempVariable(rightVar);

    if (operatorSymbol == "*")
    {
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(leftVar);
        params.push_back(rightVar);
        MulInstr *mulInstr = new MulInstr(currentBlock, params);
        currentBlock->AddIRInstr(mulInstr);
    }

    else if (operatorSymbol == "/")
    {
        std::vector<VarData> params;
        params.push_back(newVar);
        params.push_back(leftVar);
        params.push_back(rightVar);
        currentBlock->AddIRInstr(new DivInstr(currentBlock, params));
    }

    return newVar;
}

antlrcpp::Any Visitor::visitParenthesis(ifccParser::ParenthesisContext *ctx)
{
    return visit(ctx->expr());
}

antlrcpp::Any Visitor::visitBitwiseOp(ifccParser::BitwiseOpContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);

    std::string operatorSymbol = ctx->OP_BITWISE()->getText();
    VarData leftVar = visit(ctx->expr(0)).as<VarData>();
    VarData rightVar = visit(ctx->expr(1)).as<VarData>();

    std::vector<VarData> params;
    params.push_back(newVar);
    params.push_back(leftVar);
    params.push_back(rightVar);

    /* |, &,ˆ, >>, << */
    if (operatorSymbol == "|")
    {
        currentBlock->AddIRInstr(new BitOrInstr(currentBlock, params));
    }
    else if (operatorSymbol == "&")
    {
        currentBlock->AddIRInstr(new BitAndInstr(currentBlock, params));
    }
    else if (operatorSymbol == "^")
    {
        currentBlock->AddIRInstr(new BitXorInstr(currentBlock, params));
    }
    else if (operatorSymbol == ">>")
    {
        currentBlock->AddIRInstr(new BitRightShiftInstr(currentBlock, params));
    }
    else if (operatorSymbol == "<<")
    {
        currentBlock->AddIRInstr(new BitLeftShiftInstr(currentBlock, params));
    }

    return newVar;
}

antlrcpp::Any Visitor::visitCompare(ifccParser::CompareContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);

    std::string operatorSymbol = ctx->OP_COMPARE()->getText();
    VarData leftVar = visit(ctx->expr(0)).as<VarData>();
    VarData rightVar = visit(ctx->expr(1)).as<VarData>();

    std::vector<VarData> params;
    params.push_back(newVar);
    params.push_back(leftVar);
    params.push_back(rightVar);

    /* '<' | '>' | '<=' | '>=' | '==' | '!=' */
    if (operatorSymbol == "<")
    {
        currentBlock->AddIRInstr(new CmpLtInstr(currentBlock, params));
    }
    else if (operatorSymbol == ">")
    {
        currentBlock->AddIRInstr(new CmpGtInstr(currentBlock, params));
    }
    else if (operatorSymbol == "<=")
    {
        currentBlock->AddIRInstr(new CmpLeInstr(currentBlock, params));
    }
    else if (operatorSymbol == ">=")
    {
        currentBlock->AddIRInstr(new CmpGeInstr(currentBlock, params));
    }
    else if (operatorSymbol == "==")
    {
        currentBlock->AddIRInstr(new CmpEqInstr(currentBlock, params));
    }
    else if (operatorSymbol == "!=")
    {
        currentBlock->AddIRInstr(new CmpNeqInstr(currentBlock, params));
    }

    return newVar;
}

antlrcpp::Any Visitor::visitCall(ifccParser::CallContext *ctx)
{
    visitFunctionCall(ctx->functionCall());
    return 0;
}

antlrcpp::Any Visitor::visitCallAndGet(ifccParser::CallAndGetContext *ctx)
{
    // check function is not void: visit children, get return value, check if return value is void
    VarData returnedVar = visitFunctionCall(ctx->functionCall());

    // check if returnedVar is void
    std::string functionName = ctx->functionCall()->VAR()->getText();
    Function *function = IR.getFunction(functionName);
    if (returnedVar.GetTypeName() == TYPE_VOID)
    {
        VoidFunctionCallError *errorCustom = new VoidFunctionCallError(*function);
        throwError(errorCustom);
    }

    return returnedVar;
}

antlrcpp::Any Visitor::visitFunctionCall(ifccParser::FunctionCallContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();

    // std::string functionName = ctx->getText();
    // functionName = functionName.substr(0, functionName.find('(')); // remove all characters starting with first '('

    // TODO: check if function is defined (already known)
    // NOTE: putchar and getchar are always defined
    std::string functionName = ctx->VAR()->getText();
    Function *function = IR.getFunction(functionName); // TODO: check if function is defined

    // get all parameters
    std::vector<VarData> params;
    for (int i = 0; i < (int)ctx->expr().size(); i++)
    {
        VarData param = visit(ctx->expr(i)).as<VarData>();
        params.push_back(param);
    }

    // TODO: check params types are correct

    // 16 bit alignment: determine if a shift is needed to complete alignment
    int nbOfPushedParams = params.size() - 6;
    bool isStackAligned = true; // at 6 params or less, stack is already aligned
    if (nbOfPushedParams > 0)
    {
        // check if stack is aligned
        if ((nbOfPushedParams * 8) % 16 != 0)
        {
            isStackAligned = false;

            // misaligned: need to shift 8 bytes to align
            // add tmp var to pass nbToAddToRSP to AddToRSPInstr
            std::vector<VarData> paramsSTRI;
            VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);
            newVar.SetValue(8); // shift 8 bytes
            paramsSTRI.push_back(newVar);
            currentBlock->AddIRInstr(new SubToRSPInstr(currentBlock, paramsSTRI));
        }
    }

    // generate move instructions for all parameters
    std::vector<std::string> registers = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    int counter = 0;
    std::vector<IRInstr *> moveParamIRInstrs;
    for (VarData currentParam : params)
    {
        std::vector<VarData> moveParams;
        moveParams.push_back(currentParam);

        // TODO: refactor this to be shorter
        if (counter < 6)
        {
            // pass 6 first params to registers
            moveParamIRInstrs.push_back(
                new MoveFunctionParamInstr(
                    currentBlock,
                    moveParams,
                    registers[counter]));
        }
        else
        {
            // pass extra params to stack
            std::vector<VarData> moveParams;
            moveParams.push_back(currentParam);
            moveParamIRInstrs.push_back(
                new MoveFunctionParamInstr(
                    currentBlock,
                    moveParams,
                    cfg->getVariableManager()));
        }
        counter++;
    }

    // reverse instruction order (C takes params in reverse order (from right to left))
    std::reverse(moveParamIRInstrs.begin(), moveParamIRInstrs.end());
    for (IRInstr *currentInstr : moveParamIRInstrs)
    {
        currentBlock->AddIRInstr(currentInstr);
    }

    // call function
    currentBlock->AddIRInstr(new CallInstr(currentBlock, functionName, params));

    // remove (clean) extra params from stack (every push is a quad (8 bytes))
    if (nbOfPushedParams > 0)
    {
        // compute closest power of 16 (alignment) to nb of pushed params to stack
        int nbToAddToRSP;
        if (isStackAligned)
        {
            nbToAddToRSP = nbOfPushedParams * 8;
        }
        else
        {
            nbToAddToRSP = (nbOfPushedParams + 1) * 8;
        }

        std::vector<VarData> paramsATRI;
        // add tmp var to pass nbToAddToRSP to AddToRSPInstr
        VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);
        newVar.SetValue(nbToAddToRSP);
        paramsATRI.push_back(newVar);
        currentBlock->AddIRInstr(new AddToRSPInstr(currentBlock, paramsATRI));
    }

    // return new tmp var with type of return value
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), function->getReturnType());

    // before returning, save new tmp var to the stack
    std::vector<VarData> paramsSaveTmpVar;
    paramsSaveTmpVar.push_back(newVar);
    switch (newVar.GetTypeName())
    {
    case TYPE_INT:
        currentBlock->AddIRInstr(
            new MoveFunctionReturnedValueInstr(currentBlock, paramsSaveTmpVar));
        break;
    case TYPE_CHAR:
        currentBlock->AddIRInstr(
            new MoveFunctionReturnedValueInstr(currentBlock, paramsSaveTmpVar));
        break;
    case TYPE_VOID:
        break;
    default:
        break;
    }

    return newVar;
}

antlrcpp::Any Visitor::visitIfElseStatement(ifccParser::IfElseStatementContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    VarData exprResult = visit(ctx->expr());

    std::vector<VarData> params;
    params.push_back(exprResult);

    currentBlock->AddIRInstr(new ControlStructInstr(currentBlock, params));

    Block *lastBlock = currentBlock;

    Block *ifBlock = cfg->AddBlock();
    lastBlock->setExitTrue(ifBlock); // link the block

    Block *elseBlock;
    if (ctx->ELSE())
    {
        elseBlock = cfg->AddBlock();
    }

    Block *endIfBlock = cfg->AddBlock(); // end if block

    ifBlock->setExitTrue(endIfBlock); // link the block

    currentBlock = ifBlock;
    visit(ctx->block(0));
    if (ctx->ELSE())
    {
        elseBlock->setExitTrue(endIfBlock);
        lastBlock->setExitFalse(elseBlock);
        currentBlock = elseBlock;
        visit(ctx->block(1));
    }
    else
    {
        lastBlock->setExitFalse(endIfBlock);
    }
    currentBlock = endIfBlock;
    return 0;
}

antlrcpp::Any Visitor::visitWhileStatement(ifccParser::WhileStatementContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    Block *lastBlock = currentBlock;

    Block *conditionBlock = cfg->AddBlock(); // add test block to eval condition
    lastBlock->setExitTrue(conditionBlock);

    currentBlock = conditionBlock; // compute the test
    VarData exprResult = visit(ctx->expr());
    std::vector<VarData> params;
    params.push_back(exprResult);
    currentBlock->AddIRInstr(new ControlStructInstr(currentBlock, params));

    Block *trueBlock = cfg->AddBlock(); // add true block and link it
    conditionBlock->setExitTrue(trueBlock);

    Block *falseBlock = cfg->AddBlock(); // continue to the false block

    currentBlock = trueBlock; // compute the true block
    visit(ctx->block());

    currentBlock->setExitTrue(conditionBlock); // loop to the test from the current block

    conditionBlock->setExitFalse(falseBlock);

    currentBlock = falseBlock;
    return 0;
}

antlrcpp::Any Visitor::visitUnaryOp(ifccParser::UnaryOpContext *ctx)
{
    ControlFlowGraph *cfg = currentFunction->getControlFlowGraph();
    VarData newVar = cfg->add_to_symbol_table("#tmp", ctx->getStart()->getLine(), TYPE_INT);

    VarData currVar = visit(ctx->expr()).as<VarData>();
    cfg->removeTempVariable(currVar);

    std::vector<VarData> params;
    params.push_back(newVar);
    params.push_back(currVar);

    if (ctx->MINUS)
    {
        // Throwing an error in case of a double minus
        /*if(ctx->expr()->getText().substr(0,1) == "-")
        {

        }*/
        std::cout << ctx->getText() << std::endl;
        currentBlock->AddIRInstr(new NegInstr(currentBlock, params));
    }
    else if (ctx->OP_UNARY())
    {
        std::string operatorSymbol = ctx->OP_UNARY()->getText();
        if (operatorSymbol == "!")
        {
            currentBlock->AddIRInstr(new BitNotInstr(currentBlock, params));
        }
        else if (operatorSymbol == "~")
        {
            currentBlock->AddIRInstr(new BitComplementInstr(currentBlock, params));
        }
    }

    return newVar;
}
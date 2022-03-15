
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ifccParser.
 */
class  ifccVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ifccParser.
   */
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *context) = 0;

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *context) = 0;

    virtual antlrcpp::Any visitVarDefine(ifccParser::VarDefineContext *context) = 0;

    virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *context) = 0;

    virtual antlrcpp::Any visitParenthesis(ifccParser::ParenthesisContext *context) = 0;

    virtual antlrcpp::Any visitValue(ifccParser::ValueContext *context) = 0;

    virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *context) = 0;


};


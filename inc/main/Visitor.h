#pragma once

#include "ir/IntermediateRepresentation.h"
#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "variable/VarData.h"
#include "variable/VariableManager.h"
#include "warning/WarningManager.h"
#include "error/ErrorManager.h"
#include "ir/flow/ControlFlowGraph.h"
#include "BaseVisitor.h"
#include "error/symbols/UndeclaredVariableError.h"

#include <map>

class  Visitor : public BaseVisitor {
	private:
		// https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
		


	public:
		Visitor();
		~Visitor();

		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
		virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override;
		virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *ctx) override;
		virtual antlrcpp::Any visitVarDefine(ifccParser::VarDefineContext *ctx) override;
		virtual antlrcpp::Any visitVarDefineMember(ifccParser::VarDefineMemberContext *ctx) override;
		virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;
		virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;
		virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;
		virtual antlrcpp::Any visitParenthesis(ifccParser::ParenthesisContext *ctx) override;
        virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override;
};


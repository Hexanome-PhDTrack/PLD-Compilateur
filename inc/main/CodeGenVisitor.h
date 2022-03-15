#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "variable/VarData.h"
#include "variable/VariableManager.h"
#include "warning/WarningManager.h"
#include "error/ErrorManager.h"
#include "BaseVisitor.h"

#include <map>

class  CodeGenVisitor : public BaseVisitor {
	private:
		// https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile
		VariableManager varManager;

	public:
		CodeGenVisitor();
		~CodeGenVisitor();
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
		virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override;
		virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *ctx) override;
		virtual antlrcpp::Any visitVarDefine(ifccParser::VarDefineContext *ctx) override;
		virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;
		virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;
		virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;
		virtual antlrcpp::Any visitParenthesis(ifccParser::ParenthesisContext *ctx) override;

		// getters
		VariableManager getManager() { return varManager; }
};


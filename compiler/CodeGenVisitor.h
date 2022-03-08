#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "variable/VarData.h"

#include "variable/VariableManager.h"

#include <map>

class WarningChecker; // fix circular dependency

class  CodeGenVisitor : public ifccBaseVisitor {
	private:
		VariableManager varManager;

		//std::unique_ptr<WarningChecker> warningChecker;
		//WarningChecker * warningChecker;
		void checkWarnings();

	public:
		CodeGenVisitor();
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
		virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override;
		virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *ctx) override;
		virtual antlrcpp::Any visitVarDefine(ifccParser::VarDefineContext *ctx) override;
		virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;
		virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;
		virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;

		// getters
		VariableManager getManager() { return varManager; }
		
		
};


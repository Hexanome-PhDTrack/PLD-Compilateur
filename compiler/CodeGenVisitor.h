#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "variable/VarData.h"
#include "warning/WarningChecker.h"

#include "variable/VariableManager.h"

#include <map>

class  CodeGenVisitor : public ifccBaseVisitor {
	private:
		WarningChecker warningChecker;

	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
		virtual antlrcpp::Any visitExpr(ifccParser::ExprContext *ctx) override;
		virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *ctx) override;
		virtual antlrcpp::Any visitVarDefine(ifccParser::VarDefineContext *ctx) override;
		virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;
		virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;

		// getters
		VariableManager getManager() { return varManager; }

		// wrappers
		inline void checkWarnings() {
			warningChecker.CheckForWarnings(*this);
			warningChecker.LogWarnings();
		}

	private:
		VariableManager varManager;
};


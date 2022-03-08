#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include "variable/VarData.h"
#include "warning/WarningChecker.h"

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

		// getters
		std::map<std::string, VarData> getMapVariables() { return varData; }

		// wrappers
		inline void checkWarnings() {
			warningChecker.CheckForWarnings(*this);
			warningChecker.LogWarnings();
		}

	private:
		int currentVarIndex = 0;
		std::map<std::string, VarData> varData;
};


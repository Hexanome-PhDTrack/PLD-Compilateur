#pragma once

#include <map>
#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"


class  CodeGenVisitor : public ifccBaseVisitor {
	public:
		virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override ;
		virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *ctx) override;
		virtual antlrcpp::Any visitConstAssign(ifccParser::ConstAssignContext *ctx) override;

	private:
		int current_var_index = 0;
		std::map<std::string, int> var_indexes;
};


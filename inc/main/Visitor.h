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
#include "error/symbols/MultipleDeclarationError.h"
#include "error/symbols/UndeclaredVariableError.h"
#include "warning/DividingByZeroWarning.h"
#include "ir/block/Block.h"

#include <map>
#include <iostream>
#include <fstream>

class  Visitor : public BaseVisitor {
	private:

	public:
		Visitor();
		~Visitor();
		virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override;
        virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
        virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *ctx) override;
        virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override;
        virtual antlrcpp::Any visitInstr(ifccParser::InstrContext *ctx) override;
        virtual antlrcpp::Any visitFuncReturn(ifccParser::FuncReturnContext *ctx) override;
		virtual antlrcpp::Any visitVarAssign(ifccParser::VarAssignContext *ctx) override;
		virtual antlrcpp::Any visitVarDefine(ifccParser::VarDefineContext *ctx) override;
		virtual antlrcpp::Any visitVarDefineMember(ifccParser::VarDefineMemberContext *ctx) override;
		virtual antlrcpp::Any visitValue(ifccParser::ValueContext *ctx) override;
		virtual antlrcpp::Any visitAddSub(ifccParser::AddSubContext *ctx) override;
		virtual antlrcpp::Any visitMulDiv(ifccParser::MulDivContext *ctx) override;
		virtual antlrcpp::Any visitParenthesis(ifccParser::ParenthesisContext *ctx) override;
		// getters
};


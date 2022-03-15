
// Generated from ifcc.g4 by ANTLR 4.7.2


#include "ifccVisitor.h"

#include "ifccParser.h"


using namespace antlrcpp;
using namespace antlr4;

ifccParser::ifccParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ifccParser::~ifccParser() {
  delete _interpreter;
}

std::string ifccParser::getGrammarFileName() const {
  return "ifcc.g4";
}

const std::vector<std::string>& ifccParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ifccParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- AxiomContext ------------------------------------------------------------------

ifccParser::AxiomContext::AxiomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::ProgContext* ifccParser::AxiomContext::prog() {
  return getRuleContext<ifccParser::ProgContext>(0);
}


size_t ifccParser::AxiomContext::getRuleIndex() const {
  return ifccParser::RuleAxiom;
}

antlrcpp::Any ifccParser::AxiomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAxiom(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::AxiomContext* ifccParser::axiom() {
  AxiomContext *_localctx = _tracker.createInstance<AxiomContext>(_ctx, getState());
  enterRule(_localctx, 0, ifccParser::RuleAxiom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(12);
    prog();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgContext ------------------------------------------------------------------

ifccParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::ProgContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::ProgContext::RETURN() {
  return getToken(ifccParser::RETURN, 0);
}

ifccParser::ComputedValueContext* ifccParser::ProgContext::computedValue() {
  return getRuleContext<ifccParser::ComputedValueContext>(0);
}

std::vector<ifccParser::ExprContext *> ifccParser::ProgContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::ProgContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}


size_t ifccParser::ProgContext::getRuleIndex() const {
  return ifccParser::RuleProg;
}

antlrcpp::Any ifccParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ProgContext* ifccParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 2, ifccParser::RuleProg);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(14);
    match(ifccParser::TYPE);
    setState(15);
    match(ifccParser::T__0);
    setState(16);
    match(ifccParser::T__1);
    setState(17);
    match(ifccParser::T__2);
    setState(18);
    match(ifccParser::T__3);
    setState(22);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::TYPE

    || _la == ifccParser::VAR) {
      setState(19);
      expr();
      setState(24);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(25);
    match(ifccParser::RETURN);
    setState(26);
    computedValue(0);
    setState(27);
    match(ifccParser::T__4);
    setState(28);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ifccParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::VarAssignContext* ifccParser::ExprContext::varAssign() {
  return getRuleContext<ifccParser::VarAssignContext>(0);
}

ifccParser::VarDefineContext* ifccParser::ExprContext::varDefine() {
  return getRuleContext<ifccParser::VarDefineContext>(0);
}


size_t ifccParser::ExprContext::getRuleIndex() const {
  return ifccParser::RuleExpr;
}

antlrcpp::Any ifccParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ExprContext* ifccParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 4, ifccParser::RuleExpr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(32);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::VAR: {
        enterOuterAlt(_localctx, 1);
        setState(30);
        varAssign();
        break;
      }

      case ifccParser::TYPE: {
        enterOuterAlt(_localctx, 2);
        setState(31);
        varDefine();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarAssignContext ------------------------------------------------------------------

ifccParser::VarAssignContext::VarAssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VarAssignContext::VAR() {
  return getToken(ifccParser::VAR, 0);
}

ifccParser::ComputedValueContext* ifccParser::VarAssignContext::computedValue() {
  return getRuleContext<ifccParser::ComputedValueContext>(0);
}


size_t ifccParser::VarAssignContext::getRuleIndex() const {
  return ifccParser::RuleVarAssign;
}

antlrcpp::Any ifccParser::VarAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVarAssign(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VarAssignContext* ifccParser::varAssign() {
  VarAssignContext *_localctx = _tracker.createInstance<VarAssignContext>(_ctx, getState());
  enterRule(_localctx, 6, ifccParser::RuleVarAssign);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    match(ifccParser::VAR);
    setState(35);
    match(ifccParser::T__6);
    setState(36);
    computedValue(0);
    setState(37);
    match(ifccParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefineContext ------------------------------------------------------------------

ifccParser::VarDefineContext::VarDefineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VarDefineContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::VarDefineContext::VAR() {
  return getToken(ifccParser::VAR, 0);
}

ifccParser::ComputedValueContext* ifccParser::VarDefineContext::computedValue() {
  return getRuleContext<ifccParser::ComputedValueContext>(0);
}


size_t ifccParser::VarDefineContext::getRuleIndex() const {
  return ifccParser::RuleVarDefine;
}

antlrcpp::Any ifccParser::VarDefineContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVarDefine(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VarDefineContext* ifccParser::varDefine() {
  VarDefineContext *_localctx = _tracker.createInstance<VarDefineContext>(_ctx, getState());
  enterRule(_localctx, 8, ifccParser::RuleVarDefine);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(39);
    match(ifccParser::TYPE);
    setState(40);
    match(ifccParser::VAR);
    setState(43);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ifccParser::T__6) {
      setState(41);
      match(ifccParser::T__6);
      setState(42);
      computedValue(0);
    }
    setState(45);
    match(ifccParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComputedValueContext ------------------------------------------------------------------

ifccParser::ComputedValueContext::ComputedValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::ComputedValueContext::getRuleIndex() const {
  return ifccParser::RuleComputedValue;
}

void ifccParser::ComputedValueContext::copyFrom(ComputedValueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AddSubContext ------------------------------------------------------------------

std::vector<ifccParser::ComputedValueContext *> ifccParser::AddSubContext::computedValue() {
  return getRuleContexts<ifccParser::ComputedValueContext>();
}

ifccParser::ComputedValueContext* ifccParser::AddSubContext::computedValue(size_t i) {
  return getRuleContext<ifccParser::ComputedValueContext>(i);
}

tree::TerminalNode* ifccParser::AddSubContext::OP_ADD_SUB() {
  return getToken(ifccParser::OP_ADD_SUB, 0);
}

ifccParser::AddSubContext::AddSubContext(ComputedValueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::AddSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAddSub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesisContext ------------------------------------------------------------------

ifccParser::ComputedValueContext* ifccParser::ParenthesisContext::computedValue() {
  return getRuleContext<ifccParser::ComputedValueContext>(0);
}

ifccParser::ParenthesisContext::ParenthesisContext(ComputedValueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::ParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitParenthesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ValueContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::ValueContext::VAR() {
  return getToken(ifccParser::VAR, 0);
}

tree::TerminalNode* ifccParser::ValueContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}

ifccParser::ValueContext::ValueContext(ComputedValueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivContext ------------------------------------------------------------------

std::vector<ifccParser::ComputedValueContext *> ifccParser::MulDivContext::computedValue() {
  return getRuleContexts<ifccParser::ComputedValueContext>();
}

ifccParser::ComputedValueContext* ifccParser::MulDivContext::computedValue(size_t i) {
  return getRuleContext<ifccParser::ComputedValueContext>(i);
}

tree::TerminalNode* ifccParser::MulDivContext::OP_MUL_DIV() {
  return getToken(ifccParser::OP_MUL_DIV, 0);
}

ifccParser::MulDivContext::MulDivContext(ComputedValueContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::MulDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMulDiv(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ComputedValueContext* ifccParser::computedValue() {
   return computedValue(0);
}

ifccParser::ComputedValueContext* ifccParser::computedValue(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ifccParser::ComputedValueContext *_localctx = _tracker.createInstance<ComputedValueContext>(_ctx, parentState);
  ifccParser::ComputedValueContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, ifccParser::RuleComputedValue, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(53);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::T__1: {
        _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(48);
        match(ifccParser::T__1);
        setState(49);
        computedValue(0);
        setState(50);
        match(ifccParser::T__2);
        break;
      }

      case ifccParser::VAR:
      case ifccParser::CONST: {
        _localctx = _tracker.createInstance<ValueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(52);
        _la = _input->LA(1);
        if (!(_la == ifccParser::VAR

        || _la == ifccParser::CONST)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(63);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(61);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivContext>(_tracker.createInstance<ComputedValueContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleComputedValue);
          setState(55);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(56);
          match(ifccParser::OP_MUL_DIV);
          setState(57);
          computedValue(4);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubContext>(_tracker.createInstance<ComputedValueContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleComputedValue);
          setState(58);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(59);
          match(ifccParser::OP_ADD_SUB);
          setState(60);
          computedValue(3);
          break;
        }

        } 
      }
      setState(65);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool ifccParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 5: return computedValueSempred(dynamic_cast<ComputedValueContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ifccParser::computedValueSempred(ComputedValueContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ifccParser::_decisionToDFA;
atn::PredictionContextCache ifccParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ifccParser::_atn;
std::vector<uint16_t> ifccParser::_serializedATN;

std::vector<std::string> ifccParser::_ruleNames = {
  "axiom", "prog", "expr", "varAssign", "varDefine", "computedValue"
};

std::vector<std::string> ifccParser::_literalNames = {
  "", "'main'", "'('", "')'", "'{'", "';'", "'}'", "'='", "'return'", "'int'"
};

std::vector<std::string> ifccParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "RETURN", "TYPE", "OP_MUL_DIV", "OP_ADD_SUB", 
  "VAR", "CONST", "COMMENT", "DIRECTIVE", "WS"
};

dfa::Vocabulary ifccParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ifccParser::_tokenNames;

ifccParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x12, 0x45, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x7, 0x3, 0x17, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x1a, 0xb, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0x23, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x2e, 0xa, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x5, 0x7, 0x38, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x40, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x43, 
    0xb, 0x7, 0x3, 0x7, 0x2, 0x3, 0xc, 0x8, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0x2, 0x3, 0x3, 0x2, 0xe, 0xf, 0x2, 0x44, 0x2, 0xe, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x10, 0x3, 0x2, 0x2, 0x2, 0x6, 0x22, 0x3, 0x2, 0x2, 0x2, 0x8, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x29, 0x3, 0x2, 0x2, 0x2, 0xc, 0x37, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0xf, 0x5, 0x4, 0x3, 0x2, 0xf, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x11, 0x7, 0xb, 0x2, 0x2, 0x11, 0x12, 0x7, 0x3, 0x2, 0x2, 0x12, 
    0x13, 0x7, 0x4, 0x2, 0x2, 0x13, 0x14, 0x7, 0x5, 0x2, 0x2, 0x14, 0x18, 
    0x7, 0x6, 0x2, 0x2, 0x15, 0x17, 0x5, 0x6, 0x4, 0x2, 0x16, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x17, 0x1a, 0x3, 0x2, 0x2, 0x2, 0x18, 0x16, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x19, 0x3, 0x2, 0x2, 0x2, 0x19, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0x7, 0xa, 0x2, 0x2, 
    0x1c, 0x1d, 0x5, 0xc, 0x7, 0x2, 0x1d, 0x1e, 0x7, 0x7, 0x2, 0x2, 0x1e, 
    0x1f, 0x7, 0x8, 0x2, 0x2, 0x1f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x20, 0x23, 
    0x5, 0x8, 0x5, 0x2, 0x21, 0x23, 0x5, 0xa, 0x6, 0x2, 0x22, 0x20, 0x3, 
    0x2, 0x2, 0x2, 0x22, 0x21, 0x3, 0x2, 0x2, 0x2, 0x23, 0x7, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x25, 0x7, 0xe, 0x2, 0x2, 0x25, 0x26, 0x7, 0x9, 0x2, 
    0x2, 0x26, 0x27, 0x5, 0xc, 0x7, 0x2, 0x27, 0x28, 0x7, 0x7, 0x2, 0x2, 
    0x28, 0x9, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x7, 0xb, 0x2, 0x2, 0x2a, 
    0x2d, 0x7, 0xe, 0x2, 0x2, 0x2b, 0x2c, 0x7, 0x9, 0x2, 0x2, 0x2c, 0x2e, 
    0x5, 0xc, 0x7, 0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x7, 0x7, 
    0x2, 0x2, 0x30, 0xb, 0x3, 0x2, 0x2, 0x2, 0x31, 0x32, 0x8, 0x7, 0x1, 
    0x2, 0x32, 0x33, 0x7, 0x4, 0x2, 0x2, 0x33, 0x34, 0x5, 0xc, 0x7, 0x2, 
    0x34, 0x35, 0x7, 0x5, 0x2, 0x2, 0x35, 0x38, 0x3, 0x2, 0x2, 0x2, 0x36, 
    0x38, 0x9, 0x2, 0x2, 0x2, 0x37, 0x31, 0x3, 0x2, 0x2, 0x2, 0x37, 0x36, 
    0x3, 0x2, 0x2, 0x2, 0x38, 0x41, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0xc, 
    0x5, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0xc, 0x2, 0x2, 0x3b, 0x40, 0x5, 0xc, 
    0x7, 0x6, 0x3c, 0x3d, 0xc, 0x4, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0xd, 0x2, 
    0x2, 0x3e, 0x40, 0x5, 0xc, 0x7, 0x5, 0x3f, 0x39, 0x3, 0x2, 0x2, 0x2, 
    0x3f, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x40, 0x43, 0x3, 0x2, 0x2, 0x2, 0x41, 
    0x3f, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x8, 0x18, 0x22, 
    0x2d, 0x37, 0x3f, 0x41, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ifccParser::Initializer ifccParser::_init;

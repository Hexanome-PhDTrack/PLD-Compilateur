
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  ifccParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    RETURN = 8, TYPE = 9, OP_MUL_DIV = 10, OP_ADD_SUB = 11, VAR = 12, CONST = 13, 
    COMMENT = 14, DIRECTIVE = 15, WS = 16
  };

  enum {
    RuleAxiom = 0, RuleProg = 1, RuleExpr = 2, RuleVarAssign = 3, RuleVarDefine = 4, 
    RuleComputedValue = 5
  };

  ifccParser(antlr4::TokenStream *input);
  ~ifccParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class AxiomContext;
  class ProgContext;
  class ExprContext;
  class VarAssignContext;
  class VarDefineContext;
  class ComputedValueContext; 

  class  AxiomContext : public antlr4::ParserRuleContext {
  public:
    AxiomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProgContext *prog();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AxiomContext* axiom();

  class  ProgContext : public antlr4::ParserRuleContext {
  public:
    ProgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *RETURN();
    ComputedValueContext *computedValue();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgContext* prog();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarAssignContext *varAssign();
    VarDefineContext *varDefine();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  VarAssignContext : public antlr4::ParserRuleContext {
  public:
    VarAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    ComputedValueContext *computedValue();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarAssignContext* varAssign();

  class  VarDefineContext : public antlr4::ParserRuleContext {
  public:
    VarDefineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *VAR();
    ComputedValueContext *computedValue();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDefineContext* varDefine();

  class  ComputedValueContext : public antlr4::ParserRuleContext {
  public:
    ComputedValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ComputedValueContext() = default;
    void copyFrom(ComputedValueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AddSubContext : public ComputedValueContext {
  public:
    AddSubContext(ComputedValueContext *ctx);

    std::vector<ComputedValueContext *> computedValue();
    ComputedValueContext* computedValue(size_t i);
    antlr4::tree::TerminalNode *OP_ADD_SUB();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesisContext : public ComputedValueContext {
  public:
    ParenthesisContext(ComputedValueContext *ctx);

    ComputedValueContext *computedValue();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ValueContext : public ComputedValueContext {
  public:
    ValueContext(ComputedValueContext *ctx);

    antlr4::tree::TerminalNode *VAR();
    antlr4::tree::TerminalNode *CONST();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MulDivContext : public ComputedValueContext {
  public:
    MulDivContext(ComputedValueContext *ctx);

    std::vector<ComputedValueContext *> computedValue();
    ComputedValueContext* computedValue(size_t i);
    antlr4::tree::TerminalNode *OP_MUL_DIV();
    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ComputedValueContext* computedValue();
  ComputedValueContext* computedValue(int precedence);

  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool computedValueSempred(ComputedValueContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};


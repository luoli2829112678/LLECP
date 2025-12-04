
// Generated from /home/LLECP/LLECP/STExecEngine/CompilerCore/ANTLR/STGrammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  STGrammarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, WS = 6, NEWLINE = 7, 
    COMMENT = 8, LINE_COMMENT = 9, COMMA = 10, SEMI = 11, BOOL = 12, INT = 13, 
    LREAL = 14, INT_TYPE = 15, LREAL_TYPE = 16, BOOL_TYPE = 17, IF = 18, 
    THEN = 19, ELSE = 20, ELSE_IF = 21, END_IF = 22, TO = 23, DO = 24, END_FOR = 25, 
    ASSIGN = 26, BY = 27, LOOP = 28, END_LOOP = 29, TILL = 30, BLOCK = 31, 
    END_BLOCK = 32, MULT = 33, DIV = 34, PLUS = 35, MINUS = 36, AND = 37, 
    OR = 38, NOT = 39, EQ = 40, NEQ = 41, GT = 42, LT = 43, AXIS_ENABLE = 44, 
    AXIS_DISABLE = 45, AXIS_STOP = 46, AXIS_MOVE_ABS = 47, AXIS_MOVE_REL = 48, 
    AXIS_MOVE_VEL = 49, AXIS_POS = 50, AXIS_VEL = 51, AXIS_ACC = 52, AXIS_JERK = 53, 
    AXIS_DEC = 54, AXIS_RESET = 55, AXIS_STAUTS_STATE = 56, AXIS_STAUTS_ENABLE = 57, 
    AXIS_STAUTS_MOVE = 58, DRIVE_SET_DO = 59, DRIVE_SET_AO = 60, DRIVE_STAUTS_DI = 61, 
    DRIVE_STAUTS_AI = 62, BUFFER_ENABLE = 63, BUFFER_DISABLE = 64, WAIT = 65, 
    NULL_CMD = 66, START_ANALOGFOCUSING = 67, STOP_ANALOGFOCUSING = 68, 
    START_PEG = 69, STOP_PEG = 70, ID = 71
  };

  enum {
    RuleOne_para_set_func_name = 0, RuleTwo_para_set_func_name = 1, RuleRead_func_name = 2, 
    RuleProgram = 3, RuleStatement = 4, RuleAssignment = 5, RuleExpression = 6, 
    RuleIf_statement = 7, RuleCondition = 8, RuleGlobal_var_decl = 9, RuleOne_para_function = 10, 
    RuleTwo_para_function = 11, RuleRead_set_function = 12, RuleArgumentList = 13, 
    RuleLoop_statement = 14, RuleTill_statement = 15, RuleBlock_statement = 16
  };

  explicit STGrammarParser(antlr4::TokenStream *input);

  STGrammarParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~STGrammarParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class One_para_set_func_nameContext;
  class Two_para_set_func_nameContext;
  class Read_func_nameContext;
  class ProgramContext;
  class StatementContext;
  class AssignmentContext;
  class ExpressionContext;
  class If_statementContext;
  class ConditionContext;
  class Global_var_declContext;
  class One_para_functionContext;
  class Two_para_functionContext;
  class Read_set_functionContext;
  class ArgumentListContext;
  class Loop_statementContext;
  class Till_statementContext;
  class Block_statementContext; 

  class  One_para_set_func_nameContext : public antlr4::ParserRuleContext {
  public:
    One_para_set_func_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AXIS_ENABLE();
    antlr4::tree::TerminalNode *AXIS_DISABLE();
    antlr4::tree::TerminalNode *AXIS_STOP();
    antlr4::tree::TerminalNode *AXIS_MOVE_ABS();
    antlr4::tree::TerminalNode *AXIS_MOVE_REL();
    antlr4::tree::TerminalNode *AXIS_MOVE_VEL();
    antlr4::tree::TerminalNode *AXIS_RESET();
    antlr4::tree::TerminalNode *WAIT();
    antlr4::tree::TerminalNode *BUFFER_ENABLE();
    antlr4::tree::TerminalNode *BUFFER_DISABLE();
    antlr4::tree::TerminalNode *START_ANALOGFOCUSING();
    antlr4::tree::TerminalNode *STOP_ANALOGFOCUSING();
    antlr4::tree::TerminalNode *START_PEG();
    antlr4::tree::TerminalNode *STOP_PEG();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  One_para_set_func_nameContext* one_para_set_func_name();

  class  Two_para_set_func_nameContext : public antlr4::ParserRuleContext {
  public:
    Two_para_set_func_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AXIS_POS();
    antlr4::tree::TerminalNode *AXIS_VEL();
    antlr4::tree::TerminalNode *AXIS_ACC();
    antlr4::tree::TerminalNode *AXIS_JERK();
    antlr4::tree::TerminalNode *AXIS_DEC();
    antlr4::tree::TerminalNode *DRIVE_SET_DO();
    antlr4::tree::TerminalNode *DRIVE_SET_AO();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Two_para_set_func_nameContext* two_para_set_func_name();

  class  Read_func_nameContext : public antlr4::ParserRuleContext {
  public:
    Read_func_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AXIS_STAUTS_STATE();
    antlr4::tree::TerminalNode *AXIS_STAUTS_ENABLE();
    antlr4::tree::TerminalNode *AXIS_STAUTS_MOVE();
    antlr4::tree::TerminalNode *DRIVE_STAUTS_DI();
    antlr4::tree::TerminalNode *DRIVE_STAUTS_AI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Read_func_nameContext* read_func_name();

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    AssignmentContext *assignment();
    If_statementContext *if_statement();
    Global_var_declContext *global_var_decl();
    One_para_functionContext *one_para_function();
    Two_para_functionContext *two_para_function();
    Read_set_functionContext *read_set_function();
    Loop_statementContext *loop_statement();
    Block_statementContext *block_statement();
    Till_statementContext *till_statement();
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Set1PFuncExprContext : public ExpressionContext {
  public:
    Set1PFuncExprContext(ExpressionContext *ctx);

    One_para_functionContext *one_para_function();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BoolConstContext : public ExpressionContext {
  public:
    BoolConstContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *BOOL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VarContext : public ExpressionContext {
  public:
    VarContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConstContext : public ExpressionContext {
  public:
    ConstContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *INT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Set2PFuncExprContext : public ExpressionContext {
  public:
    Set2PFuncExprContext(ExpressionContext *ctx);

    Two_para_functionContext *two_para_function();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalOpContext : public ExpressionContext {
  public:
    LogicalOpContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReadFuncExprContext : public ExpressionContext {
  public:
    ReadFuncExprContext(ExpressionContext *ctx);

    Read_set_functionContext *read_set_function();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotOpContext : public ExpressionContext {
  public:
    NotOpContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenExprContext : public ExpressionContext {
  public:
    ParenExprContext(ExpressionContext *ctx);

    ExpressionContext *expression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LREALContext : public ExpressionContext {
  public:
    LREALContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LREAL();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryOpContext : public ExpressionContext {
  public:
    BinaryOpContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *MULT();
    antlr4::tree::TerminalNode *DIV();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  If_statementContext : public antlr4::ParserRuleContext {
  public:
    If_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    std::vector<ConditionContext *> condition();
    ConditionContext* condition(size_t i);
    std::vector<antlr4::tree::TerminalNode *> THEN();
    antlr4::tree::TerminalNode* THEN(size_t i);
    antlr4::tree::TerminalNode *END_IF();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    std::vector<antlr4::tree::TerminalNode *> ELSE_IF();
    antlr4::tree::TerminalNode* ELSE_IF(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_statementContext* if_statement();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *BOOL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  Global_var_declContext : public antlr4::ParserRuleContext {
  public:
    Global_var_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_TYPE();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *BOOL_TYPE();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *LREAL_TYPE();
    antlr4::tree::TerminalNode *LREAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_var_declContext* global_var_decl();

  class  One_para_functionContext : public antlr4::ParserRuleContext {
  public:
    One_para_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    One_para_set_func_nameContext *one_para_set_func_name();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  One_para_functionContext* one_para_function();

  class  Two_para_functionContext : public antlr4::ParserRuleContext {
  public:
    Two_para_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Two_para_set_func_nameContext *two_para_set_func_name();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Two_para_functionContext* two_para_function();

  class  Read_set_functionContext : public antlr4::ParserRuleContext {
  public:
    Read_set_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Read_func_nameContext *read_func_name();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Read_set_functionContext* read_set_function();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  Loop_statementContext : public antlr4::ParserRuleContext {
  public:
    Loop_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOOP();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *THEN();
    antlr4::tree::TerminalNode *END_LOOP();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Loop_statementContext* loop_statement();

  class  Till_statementContext : public antlr4::ParserRuleContext {
  public:
    Till_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TILL();
    ConditionContext *condition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Till_statementContext* till_statement();

  class  Block_statementContext : public antlr4::ParserRuleContext {
  public:
    Block_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BLOCK();
    antlr4::tree::TerminalNode *END_BLOCK();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Block_statementContext* block_statement();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};


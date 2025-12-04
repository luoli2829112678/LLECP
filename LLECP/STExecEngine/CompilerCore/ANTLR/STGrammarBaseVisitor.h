
// Generated from STGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "STGrammarVisitor.h"


/**
 * This class provides an empty implementation of STGrammarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  STGrammarBaseVisitor : public STGrammarVisitor {
public:

  virtual std::any visitOne_para_set_func_name(STGrammarParser::One_para_set_func_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTwo_para_set_func_name(STGrammarParser::Two_para_set_func_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRead_func_name(STGrammarParser::Read_func_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgram(STGrammarParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(STGrammarParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(STGrammarParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolConst(STGrammarParser::BoolConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar(STGrammarParser::VarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConst(STGrammarParser::ConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOp(STGrammarParser::LogicalOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReadFuncExpr(STGrammarParser::ReadFuncExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotOp(STGrammarParser::NotOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(STGrammarParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLREAL(STGrammarParser::LREALContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryOp(STGrammarParser::BinaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_statement(STGrammarParser::If_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(STGrammarParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobal_var_decl(STGrammarParser::Global_var_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOne_para_function(STGrammarParser::One_para_functionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTwo_para_function(STGrammarParser::Two_para_functionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRead_set_function(STGrammarParser::Read_set_functionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(STGrammarParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop_statement(STGrammarParser::Loop_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTill_statement(STGrammarParser::Till_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock_statement(STGrammarParser::Block_statementContext *ctx) override {
    return visitChildren(ctx);
  }


};


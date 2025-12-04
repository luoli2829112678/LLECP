
// Generated from STGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "STGrammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by STGrammarParser.
 */
class  STGrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterOne_para_set_func_name(STGrammarParser::One_para_set_func_nameContext *ctx) = 0;
  virtual void exitOne_para_set_func_name(STGrammarParser::One_para_set_func_nameContext *ctx) = 0;

  virtual void enterTwo_para_set_func_name(STGrammarParser::Two_para_set_func_nameContext *ctx) = 0;
  virtual void exitTwo_para_set_func_name(STGrammarParser::Two_para_set_func_nameContext *ctx) = 0;

  virtual void enterRead_func_name(STGrammarParser::Read_func_nameContext *ctx) = 0;
  virtual void exitRead_func_name(STGrammarParser::Read_func_nameContext *ctx) = 0;

  virtual void enterProgram(STGrammarParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(STGrammarParser::ProgramContext *ctx) = 0;

  virtual void enterStatement(STGrammarParser::StatementContext *ctx) = 0;
  virtual void exitStatement(STGrammarParser::StatementContext *ctx) = 0;

  virtual void enterAssignment(STGrammarParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(STGrammarParser::AssignmentContext *ctx) = 0;

  virtual void enterSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext *ctx) = 0;
  virtual void exitSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext *ctx) = 0;

  virtual void enterBoolConst(STGrammarParser::BoolConstContext *ctx) = 0;
  virtual void exitBoolConst(STGrammarParser::BoolConstContext *ctx) = 0;

  virtual void enterVar(STGrammarParser::VarContext *ctx) = 0;
  virtual void exitVar(STGrammarParser::VarContext *ctx) = 0;

  virtual void enterConst(STGrammarParser::ConstContext *ctx) = 0;
  virtual void exitConst(STGrammarParser::ConstContext *ctx) = 0;

  virtual void enterSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext *ctx) = 0;
  virtual void exitSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext *ctx) = 0;

  virtual void enterLogicalOp(STGrammarParser::LogicalOpContext *ctx) = 0;
  virtual void exitLogicalOp(STGrammarParser::LogicalOpContext *ctx) = 0;

  virtual void enterReadFuncExpr(STGrammarParser::ReadFuncExprContext *ctx) = 0;
  virtual void exitReadFuncExpr(STGrammarParser::ReadFuncExprContext *ctx) = 0;

  virtual void enterNotOp(STGrammarParser::NotOpContext *ctx) = 0;
  virtual void exitNotOp(STGrammarParser::NotOpContext *ctx) = 0;

  virtual void enterParenExpr(STGrammarParser::ParenExprContext *ctx) = 0;
  virtual void exitParenExpr(STGrammarParser::ParenExprContext *ctx) = 0;

  virtual void enterLREAL(STGrammarParser::LREALContext *ctx) = 0;
  virtual void exitLREAL(STGrammarParser::LREALContext *ctx) = 0;

  virtual void enterBinaryOp(STGrammarParser::BinaryOpContext *ctx) = 0;
  virtual void exitBinaryOp(STGrammarParser::BinaryOpContext *ctx) = 0;

  virtual void enterIf_statement(STGrammarParser::If_statementContext *ctx) = 0;
  virtual void exitIf_statement(STGrammarParser::If_statementContext *ctx) = 0;

  virtual void enterCondition(STGrammarParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(STGrammarParser::ConditionContext *ctx) = 0;

  virtual void enterGlobal_var_decl(STGrammarParser::Global_var_declContext *ctx) = 0;
  virtual void exitGlobal_var_decl(STGrammarParser::Global_var_declContext *ctx) = 0;

  virtual void enterOne_para_function(STGrammarParser::One_para_functionContext *ctx) = 0;
  virtual void exitOne_para_function(STGrammarParser::One_para_functionContext *ctx) = 0;

  virtual void enterTwo_para_function(STGrammarParser::Two_para_functionContext *ctx) = 0;
  virtual void exitTwo_para_function(STGrammarParser::Two_para_functionContext *ctx) = 0;

  virtual void enterRead_set_function(STGrammarParser::Read_set_functionContext *ctx) = 0;
  virtual void exitRead_set_function(STGrammarParser::Read_set_functionContext *ctx) = 0;

  virtual void enterArgumentList(STGrammarParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(STGrammarParser::ArgumentListContext *ctx) = 0;

  virtual void enterLoop_statement(STGrammarParser::Loop_statementContext *ctx) = 0;
  virtual void exitLoop_statement(STGrammarParser::Loop_statementContext *ctx) = 0;

  virtual void enterTill_statement(STGrammarParser::Till_statementContext *ctx) = 0;
  virtual void exitTill_statement(STGrammarParser::Till_statementContext *ctx) = 0;

  virtual void enterBlock_statement(STGrammarParser::Block_statementContext *ctx) = 0;
  virtual void exitBlock_statement(STGrammarParser::Block_statementContext *ctx) = 0;


};


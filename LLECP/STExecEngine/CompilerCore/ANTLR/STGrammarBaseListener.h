
// Generated from STGrammar.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "STGrammarListener.h"


/**
 * This class provides an empty implementation of STGrammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  STGrammarBaseListener : public STGrammarListener {
public:

  virtual void enterOne_para_set_func_name(STGrammarParser::One_para_set_func_nameContext * /*ctx*/) override { }
  virtual void exitOne_para_set_func_name(STGrammarParser::One_para_set_func_nameContext * /*ctx*/) override { }

  virtual void enterTwo_para_set_func_name(STGrammarParser::Two_para_set_func_nameContext * /*ctx*/) override { }
  virtual void exitTwo_para_set_func_name(STGrammarParser::Two_para_set_func_nameContext * /*ctx*/) override { }

  virtual void enterRead_func_name(STGrammarParser::Read_func_nameContext * /*ctx*/) override { }
  virtual void exitRead_func_name(STGrammarParser::Read_func_nameContext * /*ctx*/) override { }

  virtual void enterProgram(STGrammarParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(STGrammarParser::ProgramContext * /*ctx*/) override { }

  virtual void enterStatement(STGrammarParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(STGrammarParser::StatementContext * /*ctx*/) override { }

  virtual void enterAssignment(STGrammarParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(STGrammarParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext * /*ctx*/) override { }
  virtual void exitSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext * /*ctx*/) override { }

  virtual void enterBoolConst(STGrammarParser::BoolConstContext * /*ctx*/) override { }
  virtual void exitBoolConst(STGrammarParser::BoolConstContext * /*ctx*/) override { }

  virtual void enterVar(STGrammarParser::VarContext * /*ctx*/) override { }
  virtual void exitVar(STGrammarParser::VarContext * /*ctx*/) override { }

  virtual void enterConst(STGrammarParser::ConstContext * /*ctx*/) override { }
  virtual void exitConst(STGrammarParser::ConstContext * /*ctx*/) override { }

  virtual void enterSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext * /*ctx*/) override { }
  virtual void exitSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext * /*ctx*/) override { }

  virtual void enterLogicalOp(STGrammarParser::LogicalOpContext * /*ctx*/) override { }
  virtual void exitLogicalOp(STGrammarParser::LogicalOpContext * /*ctx*/) override { }

  virtual void enterReadFuncExpr(STGrammarParser::ReadFuncExprContext * /*ctx*/) override { }
  virtual void exitReadFuncExpr(STGrammarParser::ReadFuncExprContext * /*ctx*/) override { }

  virtual void enterNotOp(STGrammarParser::NotOpContext * /*ctx*/) override { }
  virtual void exitNotOp(STGrammarParser::NotOpContext * /*ctx*/) override { }

  virtual void enterParenExpr(STGrammarParser::ParenExprContext * /*ctx*/) override { }
  virtual void exitParenExpr(STGrammarParser::ParenExprContext * /*ctx*/) override { }

  virtual void enterLREAL(STGrammarParser::LREALContext * /*ctx*/) override { }
  virtual void exitLREAL(STGrammarParser::LREALContext * /*ctx*/) override { }

  virtual void enterBinaryOp(STGrammarParser::BinaryOpContext * /*ctx*/) override { }
  virtual void exitBinaryOp(STGrammarParser::BinaryOpContext * /*ctx*/) override { }

  virtual void enterIf_statement(STGrammarParser::If_statementContext * /*ctx*/) override { }
  virtual void exitIf_statement(STGrammarParser::If_statementContext * /*ctx*/) override { }

  virtual void enterCondition(STGrammarParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(STGrammarParser::ConditionContext * /*ctx*/) override { }

  virtual void enterGlobal_var_decl(STGrammarParser::Global_var_declContext * /*ctx*/) override { }
  virtual void exitGlobal_var_decl(STGrammarParser::Global_var_declContext * /*ctx*/) override { }

  virtual void enterOne_para_function(STGrammarParser::One_para_functionContext * /*ctx*/) override { }
  virtual void exitOne_para_function(STGrammarParser::One_para_functionContext * /*ctx*/) override { }

  virtual void enterTwo_para_function(STGrammarParser::Two_para_functionContext * /*ctx*/) override { }
  virtual void exitTwo_para_function(STGrammarParser::Two_para_functionContext * /*ctx*/) override { }

  virtual void enterRead_set_function(STGrammarParser::Read_set_functionContext * /*ctx*/) override { }
  virtual void exitRead_set_function(STGrammarParser::Read_set_functionContext * /*ctx*/) override { }

  virtual void enterArgumentList(STGrammarParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(STGrammarParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterLoop_statement(STGrammarParser::Loop_statementContext * /*ctx*/) override { }
  virtual void exitLoop_statement(STGrammarParser::Loop_statementContext * /*ctx*/) override { }

  virtual void enterTill_statement(STGrammarParser::Till_statementContext * /*ctx*/) override { }
  virtual void exitTill_statement(STGrammarParser::Till_statementContext * /*ctx*/) override { }

  virtual void enterBlock_statement(STGrammarParser::Block_statementContext * /*ctx*/) override { }
  virtual void exitBlock_statement(STGrammarParser::Block_statementContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


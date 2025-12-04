
// Generated from /home/LLECP/LLECP/STExecEngine/CompilerCore/ANTLR/STGrammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "STGrammarParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by STGrammarParser.
 */
class  STGrammarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by STGrammarParser.
   */
    virtual std::any visitOne_para_set_func_name(STGrammarParser::One_para_set_func_nameContext *context) = 0;

    virtual std::any visitTwo_para_set_func_name(STGrammarParser::Two_para_set_func_nameContext *context) = 0;

    virtual std::any visitRead_func_name(STGrammarParser::Read_func_nameContext *context) = 0;

    virtual std::any visitProgram(STGrammarParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(STGrammarParser::StatementContext *context) = 0;

    virtual std::any visitAssignment(STGrammarParser::AssignmentContext *context) = 0;

    virtual std::any visitSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext *context) = 0;

    virtual std::any visitBoolConst(STGrammarParser::BoolConstContext *context) = 0;

    virtual std::any visitVar(STGrammarParser::VarContext *context) = 0;

    virtual std::any visitConst(STGrammarParser::ConstContext *context) = 0;

    virtual std::any visitSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext *context) = 0;

    virtual std::any visitLogicalOp(STGrammarParser::LogicalOpContext *context) = 0;

    virtual std::any visitReadFuncExpr(STGrammarParser::ReadFuncExprContext *context) = 0;

    virtual std::any visitNotOp(STGrammarParser::NotOpContext *context) = 0;

    virtual std::any visitParenExpr(STGrammarParser::ParenExprContext *context) = 0;

    virtual std::any visitLREAL(STGrammarParser::LREALContext *context) = 0;

    virtual std::any visitBinaryOp(STGrammarParser::BinaryOpContext *context) = 0;

    virtual std::any visitIf_statement(STGrammarParser::If_statementContext *context) = 0;

    virtual std::any visitCondition(STGrammarParser::ConditionContext *context) = 0;

    virtual std::any visitGlobal_var_decl(STGrammarParser::Global_var_declContext *context) = 0;

    virtual std::any visitOne_para_function(STGrammarParser::One_para_functionContext *context) = 0;

    virtual std::any visitTwo_para_function(STGrammarParser::Two_para_functionContext *context) = 0;

    virtual std::any visitRead_set_function(STGrammarParser::Read_set_functionContext *context) = 0;

    virtual std::any visitArgumentList(STGrammarParser::ArgumentListContext *context) = 0;

    virtual std::any visitLoop_statement(STGrammarParser::Loop_statementContext *context) = 0;

    virtual std::any visitTill_statement(STGrammarParser::Till_statementContext *context) = 0;

    virtual std::any visitBlock_statement(STGrammarParser::Block_statementContext *context) = 0;


};


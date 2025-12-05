// EvalVisitor.h
#pragma once

#include <unordered_map>
#include <string>
#include "Value.h"

#include "STGrammarBaseVisitor.h"
#include "STGrammarParser.h"

class EvalVisitor : public STGrammarBaseVisitor {
public:
    // 变量环境：名字 -> 值
    std::unordered_map<std::string, Value> vars;

    // ========== 顶层结构 ==========
    antlrcpp::Any visitProgram(STGrammarParser::ProgramContext *ctx) override;
    antlrcpp::Any visitStatement(STGrammarParser::StatementContext *ctx) override;

    // ========== 语句 ==========
    antlrcpp::Any visitAssignment(STGrammarParser::AssignmentContext *ctx) override;
    antlrcpp::Any visitIf_statement(STGrammarParser::If_statementContext *ctx) override;
    antlrcpp::Any visitGlobal_var_decl(STGrammarParser::Global_var_declContext *ctx) override;
    antlrcpp::Any visitLoop_statement(STGrammarParser::Loop_statementContext *ctx) override;
    antlrcpp::Any visitTill_statement(STGrammarParser::Till_statementContext *ctx) override;
    antlrcpp::Any visitBlock_statement(STGrammarParser::Block_statementContext *ctx) override;

    // ========== 条件 ==========
    antlrcpp::Any visitCondition(STGrammarParser::ConditionContext *ctx) override;

    // ========== 表达式（带 label 的那些） ==========
    antlrcpp::Any visitBinaryOp(STGrammarParser::BinaryOpContext *ctx) override;
    antlrcpp::Any visitLogicalOp(STGrammarParser::LogicalOpContext *ctx) override;
    antlrcpp::Any visitNotOp(STGrammarParser::NotOpContext *ctx) override;
    antlrcpp::Any visitVar(STGrammarParser::VarContext *ctx) override;
    antlrcpp::Any visitConst(STGrammarParser::ConstContext *ctx) override;
    antlrcpp::Any visitBoolConst(STGrammarParser::BoolConstContext *ctx) override;
    antlrcpp::Any visitLREAL(STGrammarParser::LREALContext *ctx) override;
    antlrcpp::Any visitParenExpr(STGrammarParser::ParenExprContext *ctx) override;
    antlrcpp::Any visitSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext *ctx) override;
    antlrcpp::Any visitSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext *ctx) override;
    antlrcpp::Any visitReadFuncExpr(STGrammarParser::ReadFuncExprContext *ctx) override;

    // ========== 函数调用本体 ==========
    antlrcpp::Any visitOne_para_function(STGrammarParser::One_para_functionContext *ctx) override;
    antlrcpp::Any visitTwo_para_function(STGrammarParser::Two_para_functionContext *ctx) override;
    antlrcpp::Any visitRead_set_function(STGrammarParser::Read_set_functionContext *ctx) override;

    // 小工具：把 Any 转成 Value，统一处理
    Value asValue(const antlrcpp::Any &any);
private:
    // 一些内部帮助函数
    Value callOneParaFunction(const std::string &name, const Value &arg);
    Value callTwoParaFunction(const std::string &name, const Value &arg1, const Value &arg2);
    Value callReadFunction(const std::string &name, const Value &index);
};

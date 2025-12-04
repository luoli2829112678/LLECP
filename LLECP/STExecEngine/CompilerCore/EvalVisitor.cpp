// EvalVisitor.cpp
#include "EvalVisitor.h"
#include <iostream>
#include <cstdlib>

// ========== 工具函数 ==========
Value EvalVisitor::asValue(const std::any &any)
{
    // 没值就返回 NONE
    if (!any.has_value()) {
        return Value::makeNone();
    }

    // 允许直接返回 Value
    if (any.type() == typeid(Value)) {
        return std::any_cast<Value>(any);
    }

    // 容错：允许 double / long long / int / bool
    if (any.type() == typeid(double)) {
        return Value::makeReal(std::any_cast<double>(any));
    }
    if (any.type() == typeid(long long)) {
        return Value::makeInt(std::any_cast<long long>(any));
    }
    if (any.type() == typeid(int)) {
        return Value::makeInt(std::any_cast<int>(any));
    }
    if (any.type() == typeid(bool)) {
        return Value::makeBool(std::any_cast<bool>(any));
    }

    // 其他类型暂时不处理
    return Value::makeNone();
}

// ========== 顶层 ==========
antlrcpp::Any EvalVisitor::visitProgram(STGrammarParser::ProgramContext *ctx) {
    // program : statement+ EOF;
    for (auto stmt : ctx->statement()) {
        visit(stmt);
    }
    return antlrcpp::Any();
}

antlrcpp::Any EvalVisitor::visitStatement(STGrammarParser::StatementContext *ctx) {
    // statement : (assignment | if_statement | ... ) SEMI (NEWLINE+ | EOF);
    // 这里直接 visitChildren，让它自己分派到具体的 assignment/if_statement 等
    return visitChildren(ctx);
}

// ========== 变量与赋值 ==========
antlrcpp::Any EvalVisitor::visitGlobal_var_decl(STGrammarParser::Global_var_declContext *ctx) {
    // INT_TYPE ID (ASSIGN INT)?
    // BOOL_TYPE ID (ASSIGN BOOL)?
    // LREAL_TYPE ID (ASSIGN LREAL)?

    std::string name = ctx->ID()->getText();
    Value val = Value::makeNone();

    if (ctx->INT_TYPE()) {
        if (ctx->INT()) {
            long long v = std::stoll(ctx->INT()->getText());
            val = Value::makeInt(v);
        } else {
            val = Value::makeInt(0);
        }
    } else if (ctx->BOOL_TYPE()) {
        if (ctx->BOOL()) {
            bool v = (ctx->BOOL()->getText() == "TRUE");
            val = Value::makeBool(v);
        } else {
            val = Value::makeBool(false);
        }
    } else if (ctx->LREAL_TYPE()) {
        if (ctx->LREAL()) {
            double v = std::stod(ctx->LREAL()->getText());
            val = Value::makeReal(v);
        } else {
            val = Value::makeReal(0.0);
        }
    }

    vars[name] = val;
    // std::cout << "Global var: " << name << " = " << val.toString() << std::endl;
    return antlrcpp::Any();
}

antlrcpp::Any EvalVisitor::visitAssignment(STGrammarParser::AssignmentContext *ctx) {
    // assignment : ID ASSIGN expression;
    std::string name = ctx->ID()->getText();
    Value value = asValue(visit(ctx->expression()));
    vars[name] = value;
    // std::cout << "Assign: " << name << " := " << value.toString() << std::endl;
    return antlrcpp::Any();
}

// ========== 条件 & IF ==========
antlrcpp::Any EvalVisitor::visitCondition(STGrammarParser::ConditionContext *ctx) {
    // condition : expression (EQ |NEQ| GT | LT | AND | OR ) expression | BOOL;

    if (ctx->BOOL()) {
        bool v = (ctx->BOOL()->getText() == "TRUE");
        return Value::makeBool(v);
    }

    // expression op expression
    Value left  = asValue(visit(ctx->expression(0)));
    Value right = asValue(visit(ctx->expression(1)));

    std::string op;
    if (ctx->EQ())  op = "=";
    else if (ctx->NEQ()) op = "@";
    else if (ctx->GT())  op = ">";
    else if (ctx->LT())  op = "<";
    else if (ctx->AND()) op = "AND";
    else if (ctx->OR())  op = "OR";

    bool result = false;

    if (op == "=") {
        // 数值或布尔等号，简单处理一下
        if (left.type == Value::Type::BOOL || right.type == Value::Type::BOOL)
            result = (left.toBool() == right.toBool());
        else
            result = (left.toReal() == right.toReal());
    } else if (op == "@") { // NEQ
        if (left.type == Value::Type::BOOL || right.type == Value::Type::BOOL)
            result = (left.toBool() != right.toBool());
        else
            result = (left.toReal() != right.toReal());
    } else if (op == ">") {
        result = (left.toReal() > right.toReal());
    } else if (op == "<") {
        result = (left.toReal() < right.toReal());
    } else if (op == "AND") {
        result = (left.toBool() && right.toBool());
    } else if (op == "OR") {
        result = (left.toBool() || right.toBool());
    }

    return Value::makeBool(result);
}

antlrcpp::Any EvalVisitor::visitIf_statement(STGrammarParser::If_statementContext *ctx) {
    // IF condition THEN NEWLINE+ statement+
    // ( (ELSE_IF condition THEN NEWLINE+ statement+)* )
    // (ELSE NEWLINE+ statement)? END_IF;

    // 先处理 IF 分支
    Value condVal = asValue(visit(ctx->condition(0)));
    if (condVal.toBool()) {
        // 执行第一个 THEN 里的 statement+
        auto stmts = ctx->statement();
        // 语法上，第一个 condition 对应前面一段 statement，后面的 ELSIF/ELSE 的 statement 也在同一个列表里
        // 为了简单，不做精确 mapping，直接利用 ANTLR 生成顺序：
        // 第 1 段 THEN 语句是最前面那一批，可以按 NEWLINE+ 拆出来，这里为了简单，直接全部 visitChildren
        // 更严谨可以修改语法加 label；这里先简化写法：
        for (auto s : stmts) {
            visit(s);
        }
        return antlrcpp::Any();
    }

    // TODO：如果你想精确区分 THEN / ELSIF / ELSE 对应的 statement 列表，
    // 可以把 if_statement 的语法拆得更细，用 label 标记每一段，这里先给一个简单版本。
    // 当前版本：只看第一个 condition，不处理 ELSIF / ELSE。
    // 你可以先跑通基本执行，再回头精细化 IF/ELSIF/ELSE 映射。

    return antlrcpp::Any();
}

// ========== 循环 / BLOCK / TILL ==========
antlrcpp::Any EvalVisitor::visitLoop_statement(STGrammarParser::Loop_statementContext *ctx) {
    // loop_statement : LOOP INT THEN NEWLINE+ statement+ END_LOOP ;
    int times = std::stoi(ctx->INT()->getText());

    for (int i = 0; i < times; ++i) {
        for (auto s : ctx->statement()) {
            visit(s);
        }
    }
    return antlrcpp::Any();
}

// 这里我先按“只计算一次条件”来写；
// 如果你想做成 while(till 条件) 那种逻辑，可以在外层加循环。
antlrcpp::Any EvalVisitor::visitTill_statement(STGrammarParser::Till_statementContext *ctx) {
    // TILL '('condition')' ;
    Value condVal = asValue(visit(ctx->condition()));
    // 目前只是返回一个 bool，具体语义由上层控制（例如脚本主循环里根据这个决定是否退出）
    return condVal;
}

antlrcpp::Any EvalVisitor::visitBlock_statement(STGrammarParser::Block_statementContext *ctx) {
    // BLOCK NEWLINE+ statement+ END_BLOCK ;
    for (auto s : ctx->statement()) {
        visit(s);
    }
    return antlrcpp::Any();
}

// ========== 表达式部分 ==========

// expression (PLUS | MINUS | MULT | DIV) expression  # BinaryOp
antlrcpp::Any EvalVisitor::visitBinaryOp(STGrammarParser::BinaryOpContext *ctx) {
    Value left  = asValue(visit(ctx->expression(0)));
    Value right = asValue(visit(ctx->expression(1)));

    double l = left.toReal();
    double r = right.toReal();
    Value res;

    if (ctx->PLUS()) {
        res = Value::makeReal(l + r);
    } else if (ctx->MINUS()) {
        res = Value::makeReal(l - r);
    } else if (ctx->MULT()) {
        res = Value::makeReal(l * r);
    } else if (ctx->DIV()) {
        res = Value::makeReal(l / r);
    }
    return res;
}

// expression (AND | OR ) expression  # LogicalOp
antlrcpp::Any EvalVisitor::visitLogicalOp(STGrammarParser::LogicalOpContext *ctx) {
    Value left  = asValue(visit(ctx->expression(0)));
    Value right = asValue(visit(ctx->expression(1)));

    bool l = left.toBool();
    bool r = right.toBool();
    bool res = false;

    if (ctx->AND()) res = (l && r);
    if (ctx->OR())  res = (l || r);

    return Value::makeBool(res);
}

// NOT expression  # NotOp
antlrcpp::Any EvalVisitor::visitNotOp(STGrammarParser::NotOpContext *ctx) {
    Value v = asValue(visit(ctx->expression()));
    return Value::makeBool(!v.toBool());
}

// ID  # Var
antlrcpp::Any EvalVisitor::visitVar(STGrammarParser::VarContext *ctx) {
    std::string name = ctx->ID()->getText();
    auto it = vars.find(name);
    if (it == vars.end()) {
        std::cerr << "变量未定义: " << name << std::endl;
        return Value::makeNone();
    }
    return it->second;
}

// INT  # Const
antlrcpp::Any EvalVisitor::visitConst(STGrammarParser::ConstContext *ctx) {
    long long v = std::stoll(ctx->INT()->getText());
    return Value::makeInt(v);
}

// BOOL  # BoolConst
antlrcpp::Any EvalVisitor::visitBoolConst(STGrammarParser::BoolConstContext *ctx) {
    bool v = (ctx->BOOL()->getText() == "TRUE");
    return Value::makeBool(v);
}

// LREAL  # LREAL
antlrcpp::Any EvalVisitor::visitLREAL(STGrammarParser::LREALContext *ctx) {
    double v = std::stod(ctx->LREAL()->getText());
    return Value::makeReal(v);
}

// '(' expression ')'  # ParenExpr
antlrcpp::Any EvalVisitor::visitParenExpr(STGrammarParser::ParenExprContext *ctx) {
    return visit(ctx->expression());
}

// one_para_function  # Set1PFuncExpr
antlrcpp::Any EvalVisitor::visitSet1PFuncExpr(STGrammarParser::Set1PFuncExprContext *ctx) {
    return visit(ctx->one_para_function());
}

// two_para_function  # Set2PFuncExpr
antlrcpp::Any EvalVisitor::visitSet2PFuncExpr(STGrammarParser::Set2PFuncExprContext *ctx) {
    return visit(ctx->two_para_function());
}

// read_set_function  # ReadFuncExpr
antlrcpp::Any EvalVisitor::visitReadFuncExpr(STGrammarParser::ReadFuncExprContext *ctx) {
    return visit(ctx->read_set_function());
}

// ========== 函数调用本体 ==========

// one_para_function : one_para_set_func_name '(' expression ')' ;
antlrcpp::Any EvalVisitor::visitOne_para_function(STGrammarParser::One_para_functionContext *ctx) {
    std::string fname = ctx->one_para_set_func_name()->getText();
    Value arg = asValue(visit(ctx->expression()));
    Value ret = callOneParaFunction(fname, arg);
    return ret;
}

// two_para_function : two_para_set_func_name '(' expression '#' expression ')' ;
antlrcpp::Any EvalVisitor::visitTwo_para_function(STGrammarParser::Two_para_functionContext *ctx) {
    std::string fname = ctx->two_para_set_func_name()->getText();
    Value arg1 = asValue(visit(ctx->expression(0)));
    Value arg2 = asValue(visit(ctx->expression(1)));
    Value ret = callTwoParaFunction(fname, arg1, arg2);
    return ret;
}

// read_set_function : read_func_name '[' expression ']' ;
antlrcpp::Any EvalVisitor::visitRead_set_function(STGrammarParser::Read_set_functionContext *ctx) {
    std::string fname = ctx->read_func_name()->getText();
    Value idx = asValue(visit(ctx->expression()));
    Value ret = callReadFunction(fname, idx);
    return ret;
}

// ========== 真正的“轴函数钩子” ==========

Value EvalVisitor::callOneParaFunction(const std::string &name, const Value &arg) {
    // 这里先简单打印，后面你可以接 HRPC 控制逻辑
    std::cout << "[CALL] " << name << "(" << arg.toString() << ")\n";

    // 比如：AXIS_ENABLE(axisId)
    // if (name == "AXIS_ENABLE") { ... }

    return Value::makeNone(); // 大部分控制命令不需要返回
}

Value EvalVisitor::callTwoParaFunction(const std::string &name, const Value &arg1, const Value &arg2) {
    std::cout << "[CALL] " << name << "("
              << arg1.toString() << " # " << arg2.toString() << ")\n";

    // 比如：AXIS_POS(axisId, pos)
    // if (name == "AXIS_POS") { ... }

    return Value::makeNone();
}

Value EvalVisitor::callReadFunction(const std::string &name, const Value &index) {
    std::cout << "[READ] " << name << "[" << index.toString() << "]\n";

    // 读状态时可以返回一个 Value，例如 BOOL 状态 / 实数反馈值
    // 这里先返回 0
    return Value::makeInt(0);
}

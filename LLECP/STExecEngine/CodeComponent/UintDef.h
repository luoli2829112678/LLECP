#pragma once


enum EN_LogicalStatementType
{
    LogicalStatementType_NULL = 0,
    LogicalStatementType_IF,
    LogicalStatementType_ELSIF,
    LogicalStatementType_ELSE,
    LogicalStatementType_END_IF,
    LogicalStatementType_LOOP,
    LogicalStatementType_END_LOOP,
    LogicalStatementType_FOR,
    LogicalStatementType_END_FOR,
    LogicalStatementType_WAIT,
    LogicalStatementType_THEN,
    LogicalStatementType_BY,
    LogicalStatementType_WHILE,
    LogicalStatementType_END_WHILE,
    LogicalStatementType_DO,
    LogicalStatementType_CASE,
    LogicalStatementType_OF,
    LogicalStatementType_END_CASE,
    LogicalStatementType_TO,
    LogicalStatementType_REPEAT,
    LogicalStatementType_UNTIL,
    LogicalStatementType_END_REPEAT,
    LogicalStatementType_EXIT,
    LogicalStatementType_RETURN,
    LogicalStatementType_CONTINUE,
    LogicalStatementType_DEFAULT,
};
enum EN_TokenType {

    TokenType_NULL,//空
    TokenType_INTNumber,//整数数字
    TokenType_DOUBLENumber,//小数字
    TokenType_COMMA,//分隔符字符
    TokenType_BoolLiteral,//TRUE  过渡，转换成数字
    TokenType_Operator,//操作运算符+-
    TokenType_Delimiter,//括号
    TokenType_Assignment,//赋值
    TokenType_LogicalStatement,//逻辑运算符IF/ELSE
    TokenType_Function,//函数
    TokenType_Variable,//变量
    TokenType_VariableType,//变量类型
    TokenType_Preprocessing,//预处理
    TokenType_Direction,//正负号
};
enum EN_OperatorType {
    OperatorType_NULL,
    OperatorType_PLUS,//+
    OperatorType_Subtract,//-
    OperatorType_Ride,//*
    OperatorType_Division,///
    OperatorType_Equal,//=
    OperatorType_Greater,//>
    OperatorType_Less,//<
    OperatorType_Unequal,//<>
    OperatorType_GreaterEqual,//>=
    OperatorType_LessEqual,//<=
    //OperatorType_ASSIGN,//:=
    OperatorType_LeftBracket,      // [
    OperatorType_RightBracket,     // ]
    OperatorType_ERROR
};

enum EN_DelimiterType {
    DelimiterType_NULL,
    DelimiterType_Parentheses_L,//(
    DelimiterType_Parentheses_R,//)
    DelimiterType_Bracket_L,//[
    DelimiterType_Bracket_R,//[
    DelimiterType_Braces_L,//{
    DelimiterType_Braces_R,//}
    DelimiterType_ERROR
};
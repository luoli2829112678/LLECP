#pragma once
#include<vector>
#include<string>
#include <stdint.h>
#include"CmdTypeDefine.h" 
union  UN_Param
{
    bool bParm;
    uint32_t nParm;
};

struct  ST_State
{
    bool bState;
    int nPState;
    double dState;
    long lParm;
};

enum EX_RES
{
    EX_RES_NULL,
    EX_RES_Wait,
    EX_RES_Done,
    EX_RES_Error
};
enum EN_CmdType
{
    CmdType_NULL = 0,
    //逻辑指令
    CmdType_IF,
    CmdType_ELSIF,
    CmdType_ELSE,
    CmdType_END_if,
    CmdType_LOOP,
    CmdType_END_LOOP,
    CmdType_FOR,
    CmdType_END_FOR,
    CmdType_WAIT,

    CmdType_CALCULATION,

    CmdType_ENABLE,
    CmdType_DISABLE,

    CmdType_UsrFun,

    CmdType_Max
};


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
    TokenType_Number,//数字
    TokenType_Operator,//操作运算符
    TokenType_Delimiter,//括号
    TokenType_Assignment,//赋值
    TokenType_LogicalStatement,//逻辑运算符
    TokenType_Function,//函数
    TokenType_Variable,//变量
    TokenType_VariableType,//变量类型
    TokenType_Minus,//负号
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
    OperatorType_ASSIGN,//:=
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
    DelimiterType_BracketA_L,//[
    DelimiterType_BracketA_R,//[
    DelimiterType_ERROR
};

enum EN_VariableType
{
    en_NULLType,
    en_BOOL,
    en_UINT32,
    en_INT32,
    en_DOUBLE_64,
    en_STRING,
};


union UN_TokenValue
{
    EN_OperatorType OperatorType;
    double NumberValue;
    EN_LogicalStatementType LogicalStatementType;
    EN_DelimiterType DelimiterType;
    EN_VariableType VariableType;
    uint32_t KeywordAddr;
    uint32_t FunctionAddr;
};

struct UN_BaseValue
{
    bool bData;
    int nData;
    uint32_t unData;
    double dData;
};
class ScriptValue
{
public:
    UN_BaseValue baseValue;
    std::string sData;
};
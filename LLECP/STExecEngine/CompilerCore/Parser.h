#pragma once
#include <vector>
#include <string>
#include <cctype>
#include"ParserStringDef.h"
#include"FunctionManager.h"
#include"VariableManager.h"
#include"../VariableUint/StructManager.h"
#include"../CodeComponent/BufferUint.h"
class Parser
{
private:
    //用户定义的结构体
    StructManager* m_pStructManager;
    //变量管理器
    VariableManager* m_pVariableManager;
    //函数管理器
    FunctionManager* m_pFunctionManager;
public:
    Parser(VariableManager* pVariableManager,StructManager* pStructManager,FunctionManager* pFunctionManager);
    ~Parser();
    int ParserCmd(string sCmd,CmdUint &stCmdUint);


private:
    const vector<string> symbols = {
        // 多字符符号
        SYM_ASSIGN, SYM_LE, SYM_GE, SYM_NE, SYM_RANGE,

        // 单字符符号
        SYM_PLUS, SYM_MINUS, SYM_MUL, SYM_DIV,
        SYM_GT, SYM_LT, SYM_EQ,
        SYM_SPACE,
        SYM_LPAREN, SYM_RPAREN,
        SYM_COMMA, SYM_SEMICOLON,
        SYM_COLON
    };
private:
    bool IsCharacter(const char c);
    bool IsNumber(const char c);


private:
    vector<string> SplitString(string cmd);

    BaseToken LogicalStatement_Parse(string cmd);
    BaseToken BoolLiteral_Parse(string cmd);
    //可能为变量或函数或者数组
    BaseToken Preprocessing_Parse(string cmd);
    BaseToken VariableType_Parse(string cmd);
    BaseToken Function_Parse(string cmd);
    //双字符判断要在单字符判断前
    BaseToken Assignment_Parse(string cmd);
    BaseToken Delimiter_Parse(string cmd);
    BaseToken Number_Parse(string cmd);
    BaseToken Operator_Parse(string cmd);
};

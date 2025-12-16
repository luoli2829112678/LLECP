#pragma once
#include"Calculator.h"


class Actuator
{
private:
    //用户定义的结构体
    StructManager* m_pStructManager;
    //变量管理器
    VariableManager* m_pVariableManager;
    //函数管理器
    FunctionManager* m_pFunctionManager;

    BaseToken GetVariable(BaseToken inputToken);
    ST_Result ExecuteLogicalStatement(CmdUint pCmdUint);

public:
    Actuator(VariableManager* pVariableManager,StructManager* pStructManager,FunctionManager* pFunctionManager);
    int ExecuteLine(LineUint pLineUint);
    BaseToken ExecuteCommand(CmdUint& pCmdUint);
    ~Actuator();
};

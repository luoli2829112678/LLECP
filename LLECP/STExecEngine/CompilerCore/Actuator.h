#pragma once
#include"FunctionManager.h"
#include"VariableManager.h"
#include"../VariableUint/StructManager.h"

class Actuator
{
private:
    //用户定义的结构体
    StructManager* m_pStructManager;
    //变量管理器
    VariableManager* m_pVariableManager;
    //函数管理器
    FunctionManager* m_pFunctionManager;
public:
    Actuator(VariableManager* pVariableManager,StructManager* pStructManager,FunctionManager* pFunctionManager);
    ~Actuator();
};

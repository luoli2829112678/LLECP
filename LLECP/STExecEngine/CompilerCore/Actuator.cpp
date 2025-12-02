#include"Actuator.h"

Actuator::Actuator(VariableManager* pVariableManager,StructManager* pStructManager,FunctionManager* pFunctionManager)
{
    m_pFunctionManager = pFunctionManager;
    m_pStructManager = pStructManager;
    m_pVariableManager = pVariableManager;
}

Actuator::~Actuator()
{
}

int Actuator::ExecuteCommand(CmdUint* pCmdUint)
{
    auto TokenList = pCmdUint->GetToken();
    //第一优先级变量转换
    for (size_t i = 0; i < TokenList.size(); i++)
    {
        if(TokenType_Assignment == TokenList[i].enTokenType)
        {
            TokenList[i] = GetVariable(TokenList[i]);
        }
    }
    
    //第二优先级执行函数

    //第三优先级执行逻辑语句

    //第四优先级执行赋值（调用计算器）
    return 0;
}

BaseToken Actuator::GetVariable(BaseToken inputToken)
{
    BaseToken outputToken;
    outputToken.bInit = false;
    if(TokenType_Assignment != inputToken.enTokenType)
    {
        return outputToken;
    }
    if (inputToken.KeywordAddr >= 0)
    {
        m_pVariableManager->GetVariable(inputToken.nBuffID,inputToken.KeywordAddr);
    }
    
}
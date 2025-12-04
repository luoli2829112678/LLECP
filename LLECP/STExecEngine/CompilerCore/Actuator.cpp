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

int Actuator::ExecuteLine(LineUint* pLineUint)
{
    for (;pLineUint->nCmdRunIndex < pLineUint->m_vCmd.size();)
    {
        ExecuteCommand(&pLineUint->m_vCmd[pLineUint->nCmdRunIndex]);
        if(pLineUint->m_vCmd[pLineUint->nCmdRunIndex].IsCmdRunDone())
        {
            pLineUint->nCmdRunIndex++;
        }
        else
        {
            break;
        }
    }
    if(pLineUint->nCmdRunIndex >= pLineUint->m_vCmd.size())
    {
        pLineUint->bLineRunDone = true;
    }
    return 0;
}



BaseToken Actuator::ExecuteCommand(CmdUint* pCmdUint)
{
    BaseToken result;
    auto TokenList = pCmdUint->GetToken();
    //第一优先级变量转换
    for (size_t i = 0; i < TokenList.size(); i++)
    {
        if(TokenType_Variable == TokenList[i].enTokenType)
        {
            TokenList[i] = GetVariable(TokenList[i]);
        }
    }
    
    //第二优先级执行函数
    for (size_t i = 0; i < TokenList.size(); i++)
    {
        if(TokenType_Function == TokenList[i].enTokenType)
        {
            FunctionInfo fun = m_pFunctionManager->GetFunction(TokenList[i].KeywordAddr);
            //遍历
            //层数
            int nHierarchy = -1;
            int nFunEnd = -1;
            vector<CmdUint> subCmd;
            vector<BaseToken> subToken;
            for (size_t j = i+1; i < TokenList.size(); j++)
            {
                if((nHierarchy == 0)&&(TokenList[j].KeywordAddr == DelimiterType_Parentheses_R))
                {
                    nFunEnd = j;
                    break;
                }
                if(TokenList[j].KeywordAddr == DelimiterType_Parentheses_L)
                {
                    nHierarchy++;
                    continue;
                }
                if(TokenList[j].KeywordAddr == DelimiterType_Parentheses_R)
                {
                    nHierarchy--;
                    continue;
                }
                if(TokenList[j].KeywordAddr == TokenType_COMMA)
                {
                    CmdUint tcmd;
                    tcmd.SetCmdUint(subToken);
                    subCmd.push_back(tcmd);
                    subToken.clear();
                    continue;
                }
                subToken.push_back(TokenList[j]);
            }
            vector <BaseToken> paramToken;
            //回调计算值
            for (size_t j = 0; j < subCmd.size(); j++)
            {
                paramToken.push_back(ExecuteCommand(&subCmd[j]));
            }
            //准备输入输出变量
            vector<VariableUint> InputVar;
            for (size_t j = i+1; i < paramToken.size(); j++)
            {
                InputVar.push_back(BaseToken2VariableUint(paramToken[j]));
            }
            //输入变量
            VariableUint ResultVar = fun.CallFunc(InputVar);
            BaseToken Funout = VariableUint2BaseToken(ResultVar);
            //删除函数并使用Funout替代
            TokenList.erase(TokenList.begin() + i,TokenList.begin() + nFunEnd + 1);
            TokenList.insert(TokenList.begin() + i,Funout);
        }
    }
    //第三优先级执行逻辑语句
    for (size_t i = 0; i < TokenList.size(); i++)
    {
        if(TokenType_LogicalStatement == TokenList[i].enTokenType)
        {
            //逻辑语句处理
        }
    }
    //第四优先级执行计算（调用计算器）

    //第五优先级执行赋值

    return result;
}

BaseToken Actuator::GetVariable(BaseToken inputToken)
{
    BaseToken outputToken;
    outputToken.bInit = false;
    if(TokenType_Assignment != inputToken.enTokenType)
    {
        return outputToken;
    }
    VariableUint* pVar = m_pVariableManager->GetVariable(inputToken.nBuffID,inputToken.KeywordAddr);
    //拿出偏移的最后一个类型，以此判断数据类型
    int nStructInfoID = inputToken.v_nSTOffset.back();
    switch (nStructInfoID)
    {
    case STRUCT_INFO_INT:
        {
            int32_t val = *(int16_t*)pVar->pDataAddr;
            outputToken.enTokenType = TokenType_INTNumber;
            outputToken.KeywordAddr = val;
            outputToken.bInit = true;
        }
        break;
    case STRUCT_INFO_DINT:
        {
            int32_t val = *(int32_t*)pVar->pDataAddr;
            outputToken.enTokenType = TokenType_INTNumber;
            outputToken.KeywordAddr = val;
            outputToken.bInit = true;
        }
        break;
    case STRUCT_INFO_REAL:
        {
            float val = *(float*)pVar->pDataAddr;
            outputToken.enTokenType = TokenType_DOUBLENumber;
            outputToken.KeywordAddr = val;
            outputToken.bInit = true;
        }
        break;
    case STRUCT_INFO_LREAL:
        {
            double val = *(double*)pVar->pDataAddr;
            outputToken.enTokenType = TokenType_DOUBLENumber;
            outputToken.KeywordAddr = val;
            outputToken.bInit = true;
        }
        break;
    case STRUCT_INFO_BOOL:
        {
            bool val = *(bool*)pVar->pDataAddr;
            outputToken.enTokenType = TokenType_INTNumber;
            outputToken.KeywordAddr = val?1:0;
            outputToken.bInit = true;
        }
        break;
    case STRUCT_INFO_LONG:
        {
            int64_t val = *(int64_t*)pVar->pDataAddr;
            outputToken.enTokenType = TokenType_INTNumber;
            outputToken.KeywordAddr = val;
            outputToken.bInit = true;
        }
        break; 
    default:
        printf("GetVariableERROR:Unsupported variable type!\n");
        break;
    }
    return outputToken;
}
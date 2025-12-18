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

int Actuator::ExecuteLine(LineUint pLineUint)
{
    for (;pLineUint.nCmdRunIndex < pLineUint.m_vCmd.size();)
    {
        ExecuteCommand(pLineUint.m_vCmd[pLineUint.nCmdRunIndex]);
        if(pLineUint.m_vCmd[pLineUint.nCmdRunIndex].GetResult().bIsNextCmd)
        {
            pLineUint.nCmdRunIndex++;
        }
        else
        {
            break;
        }
    }
    if(pLineUint.nCmdRunIndex >= pLineUint.m_vCmd.size())
    {
        pLineUint.bLineRunDone = true;
    }
    return 0;
}



BaseToken Actuator::ExecuteCommand(CmdUint& CmdUintIn)
{
    BaseToken result;
    std::vector<BaseToken> * TokenList = CmdUintIn.GetToken();
    //第零优先级变量声明

    //第一优先级变量转换
    for (size_t i = 0; i < TokenList->size(); i++)
    {
        //赋值前的变量不做转换
        if((TokenType_Variable == (*TokenList)[i].enTokenType)&&(TokenType_Assignment != (*TokenList)[i+1].enTokenType))
        {
            (*TokenList)[i] = GetVariable((*TokenList)[i]);
        }
    }
    //正负号处理
    for (size_t i = 0; i < TokenList->size(); i++)
    {
        if((TokenType_Direction == (*TokenList)[i].enTokenType))
        {
            //符号乘以数字
            (*TokenList)[i+1].KeywordAddr = (int)(*TokenList)[i].KeywordAddr * (*TokenList)[i+1].KeywordAddr;
        }
    }
    
    //第二优先级执行函数
    for (size_t i = 0; i < TokenList->size(); i++)
    {
        if(TokenType_Function == (*TokenList)[i].enTokenType)
        {
            FunctionInfo fun = m_pFunctionManager->GetFunction((*TokenList)[i].KeywordAddr);
            //遍历
            //层数
            int nHierarchy = 0;
            int nFunEnd = -1;
            vector<CmdUint> subCmd;
            vector<BaseToken> subToken;
            for (size_t j = i+1; i < TokenList->size(); j++)
            {
                if((nHierarchy == 0)&&((*TokenList)[j].KeywordAddr == DelimiterType_Parentheses_R))
                {
                    nFunEnd = j;
                    break;
                }
                if((*TokenList)[j].KeywordAddr == DelimiterType_Parentheses_L)
                {
                    nHierarchy++;
                    continue;
                }
                if((*TokenList)[j].KeywordAddr == DelimiterType_Parentheses_R)
                {
                    nHierarchy--;
                    continue;
                }
                if((*TokenList)[j].KeywordAddr == TokenType_COMMA)
                {

                    subToken.clear();
                    continue;
                }
                subToken.push_back((*TokenList)[j]);
            }
            vector <BaseToken> paramToken;
            //回调计算值
            for (size_t j = 0; j < subCmd.size(); j++)
            {
                paramToken.push_back(ExecuteCommand(subCmd[j]));
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
            TokenList->erase(TokenList->begin() + i,TokenList->begin() + nFunEnd + 1);
            TokenList->insert(TokenList->begin() + i,Funout);
        }
    }
    //第三优先级执行逻辑语句
    for (size_t i = 0; i < TokenList->size(); i++)
    {
        if(TokenType_LogicalStatement == (*TokenList)[i].enTokenType)
        {
            ST_Result res = ExecuteLogicalStatement(CmdUintIn);
            if(res.bResetCmd)
            {
                CmdUintIn.ResetCmd();
            }
            //返回跳转
            CmdUintIn.SetResult(res);
            //逻辑指令后不支持其他指令，直接return
            return BaseToken();
        }
    }

    // 第四优先级执行计算（调用计算器）
    int firstOpIndex = -1;
    int lastOpIndex  = -1;
    // 1查找第一个 & 最后一个运算符的位置
    if (TokenList && !TokenList->empty())
    {
        for (int i = 0; i < (int)TokenList->size(); ++i)
        {
            if ((*TokenList)[i].enTokenType == TokenType_Operator)
            {
                if (firstOpIndex == -1)
                    firstOpIndex = i;   // 第一次遇到，记录第一个位置

                lastOpIndex = i;        // 一直更新，最后一次就是最后位置
            }
        }
    }
    // 2计算并替换这一段 token
    if (firstOpIndex != -1 && lastOpIndex >= firstOpIndex)
    {
        // ① 取出要计算的这段表达式（这里是从第一个运算符到最后一个运算符）
        std::vector<BaseToken> vExpr(
            TokenList->begin() + firstOpIndex - 1,
            TokenList->begin() + lastOpIndex + 2   // 注意 +1，end 是开区间
        );

        // 丢进计算器
        BaseToken resultToken = Calculator(vExpr);

        // 用计算结果替换掉原来的那一串 token
        TokenList->erase(
            TokenList->begin() + firstOpIndex -1,
            TokenList->begin() + lastOpIndex + 2
        );
        TokenList->insert(
            TokenList->begin() + firstOpIndex -1,
            resultToken
        );
    }
    
    //第五优先级执行赋值
    for (size_t i = 0; i < TokenList->size(); i++)
    {
        if(TokenType_Assignment == (*TokenList)[i].enTokenType)
        {
            if((*TokenList).size()!=3)
            {
                printf("ExecuteCommandERROR:Assignment format error!\n");
                break;
            }
            if(TokenType_Variable != (*TokenList)[i-1].enTokenType)
            {
                printf("ExecuteCommandERROR:Left side of Assignment is not variable!\n");
                break;
            }
            //数据类型判定
            BaseToken varToken_L = GetVariable((*TokenList)[i-1]);
            switch (varToken_L.enTokenType)
            {
                case TokenType_INTNumber:
                    (*TokenList)[i+1].enTokenType = TokenType_INTNumber;
                    break;
                case TokenType_DOUBLENumber:
                    (*TokenList)[i+1].enTokenType = TokenType_DOUBLENumber;
                    break;
                
                default:
                    break;
            }
            VariableUint Var = BaseToken2VariableUint((*TokenList)[i+1]);
            m_pVariableManager->SetVariable((*TokenList)[i-1].nBuffID,(*TokenList)[i-1].KeywordAddr,Var);
            ST_Result stResult;
            stResult.bIsNextCmd = true;
            CmdUintIn.SetResult(stResult);
        }
    }
    return result;
}

BaseToken Actuator::GetVariable(BaseToken inputToken)
{
    BaseToken outputToken;
    outputToken.bInit = false;
    if(TokenType_Variable != inputToken.enTokenType)
    {
        printf("GetVariableERROR:Input token is not variable type!\n");
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
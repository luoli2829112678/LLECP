#include"Actuator.h"
ST_Result Actuator::ExecuteLogicalStatement(CmdUint* pCmdUint)
{
    //到此处时所有函数已经执行完成，所有变量已经转换为常量
    ST_Result result;
    std::vector<BaseToken>* pvToken = pCmdUint->GetToken();
    int nType = (*pvToken)[0].KeywordAddr;
    uint16_t nCmdSize = pvToken->size();
    BaseToken JudgmentResult;
    std::vector<BaseToken>v_Judgment;
    std::vector<UN_TransitionParam> v_Param;
    switch (nType)
    {
    case LogicalStatementType_IF:
    case LogicalStatementType_ELSIF:
        {
            if(nCmdSize < 3)
            {
                //IF后面没有条件，错误
                printf("ErrorExecuteLogicalStatement\n");
                break;
            }
            for (size_t i = 1; i < nCmdSize - 2; i++)
            {
                v_Judgment.push_back((*pvToken)[i]);
            }
            JudgmentResult = Calculator(v_Judgment);
            if((JudgmentResult.enTokenType == TokenType_INTNumber)&&((int)JudgmentResult.KeywordAddr != 0))
            {
                //条件成立，继续执行
                result.bIsNextLine = true;
            }
            else
            {
                //条件不成立，跳转到else或end_if
                v_Param = pCmdUint->GetCmdParam();
                if(v_Param.size() >= 1)
                {
                    result.bIsJump = true;
                    result.nJumpLinePos = v_Param[0].nParam;
                    result.nJumpCmdPos = v_Param[1].nParam;
                    result.bIsNextLine = false;
                }
                else
                {
                    //没有else或end_if，直接结束
                    result.bIsNextLine = false;
                    printf("ErrorExecuteLogicalStatement\n");
                }
            }
        }
        break;
    case LogicalStatementType_ELSE:
    case LogicalStatementType_END_IF:
        //结束IF，直接执行
        result.bIsNextLine = true;
        break;
    case LogicalStatementType_LOOP:
        if(nCmdSize < 3)
        {
            //IF后面没有条件，错误
            printf("ErrorExecuteLogicalStatement\n");
            break;
        }
        for (size_t i = 1; i < nCmdSize - 2; i++)
        {
            v_Judgment.push_back((*pvToken)[i]);
        }
        JudgmentResult = Calculator(v_Judgment);
        if(pCmdUint->GetCmdState()[0].nParam < (int)JudgmentResult.KeywordAddr)
        {
            result.bIsNextLine = true;
        }
        else
        {
            //跳出循环，跳转到end_loop
            v_Param = pCmdUint->GetCmdParam();
            if(v_Param.size() >= 2)
            {
                result.bIsJump = true;
                result.nJumpLinePos = v_Param[0].nParam;
                //循环类的·需要+1，因为end_loop会跳转回来
                result.nJumpCmdPos = v_Param[1].nParam + 1;
                result.bIsNextLine = true;
            }
            else
            {
                //没有end_loop，直接结束
                result.bIsNextLine = false;
                result.bResetCmd = true;
                printf("ErrorExecuteLogicalStatement\n");
            }
        }
        break;
    case LogicalStatementType_END_LOOP:
        //跳回LOOP处
        v_Param = pCmdUint->GetCmdParam();
        if(v_Param.size() >= 2)
        {
            result.bIsJump = true;
            result.nJumpLinePos = v_Param[0].nParam;
            result.nJumpCmdPos = v_Param[1].nParam;
            result.bIsNextLine = true;
        }
        else
        {
            //没有LOOP，直接结束
            result.bIsNextLine = false;
            printf("ErrorExecuteLogicalStatement\n");
        }
        break;
    case LogicalStatementType_WHILE:
        if(nCmdSize < 3)
        {
            //WHILE后面没有条件，错误
            printf("ErrorExecuteLogicalStatement\n");
            break;
        }
        for (size_t i = 1; i < nCmdSize - 2; i++)
        {
            v_Judgment.push_back((*pvToken)[i]);
        }
        JudgmentResult = Calculator(v_Judgment);
        if((JudgmentResult.enTokenType == TokenType_INTNumber)&&((int)JudgmentResult.KeywordAddr != 0))
        {
            //条件成立，继续执行
            result.bIsNextLine = true;
        }
        else
        {
            //条件不成立，跳转到end_while
            v_Param = pCmdUint->GetCmdParam();
            if(v_Param.size() >= 2)
            {
                result.bIsJump = true;
                result.nJumpLinePos = v_Param[0].nParam;
                result.nJumpCmdPos = v_Param[1].nParam + 1;
                result.bIsNextLine = true;
                result.bResetCmd = true;
            }
            else
            {
                //没有end_while，直接结束
                result.bIsNextLine = false;
                printf("ErrorExecuteLogicalStatement\n");
            }
        }
        break;
    case LogicalStatementType_END_WHILE:
        //跳回LOOP处
        v_Param = pCmdUint->GetCmdParam();
        if(v_Param.size() >= 2)
        {
            result.bIsJump = true;
            result.nJumpLinePos = v_Param[0].nParam;
            result.nJumpCmdPos = v_Param[1].nParam;
            result.bIsNextLine = true;
        }
        else
        {
            //没有LOOP，直接结束
            result.bIsNextLine = false;
            printf("ErrorExecuteLogicalStatement\n");
        }
        break;
    // case LogicalStatementType_FOR:
    //     break;
    default:
        break;
    }
    pCmdUint->SetResult(result);
    return result;
}
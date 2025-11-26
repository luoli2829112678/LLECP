#include"RT_Script.h"

EX_RES RT_ScriptSystem::ActuatorUint_IF(ScriptUint_Cmd* pUint_Cmd)
{
    if(pUint_Cmd->v_Token[0].TokenValue.LogicalStatementType != LogicalStatementType_IF)
    {
        return EX_RES_Error;
    }
    //找出THEN的位置
    int8_t nThenPos = -1;
    for(size_t i = 0 ;i<pUint_Cmd->v_Token.size();i++)
    {
        if((pUint_Cmd->v_Token[i].TokenType == TokenType_LogicalStatement) && (pUint_Cmd->v_Token[i].TokenValue.LogicalStatementType == LogicalStatementType_THEN))
        {
            nThenPos = i;
        }
    }
    //判断IF满足条件
    std::vector<ScriptUint_Token> v_Judging(pUint_Cmd->v_Token.begin()+1,pUint_Cmd->v_Token.end() - nThenPos);
    //计算出结果
    int8_t out = RT_ScriptCalculator(v_Judging);
    //param[LineIndex，CmdIndex]
    //寻找不满足跳转地点//ELSE  /ELSEIF //END_IF
    uint32_t LineIndex = nRunLineIndex;
    uint32_t CmdIndex = nRunCmdIndex;
    for(;nRunLineIndex<ScripList[nRunBufferIndex].GetLineNum();nRunLineIndex ++)
    {
        for(;CmdIndex<ScripList[nRunBufferIndex].v_LineList[nRunLineIndex].v_CmdList.size();CmdIndex++)
        {
            std::vector<ScriptUint_Token>  TokenList = ScripList[nRunBufferIndex].v_LineList[nRunLineIndex].v_CmdList[CmdIndex].v_Token;
            if(TokenList[0].TokenType == TokenType_LogicalStatement)
            {
                if((TokenList[0].TokenValue.LogicalStatementType == LogicalStatementType_ELSE)||
                    (TokenList[0].TokenValue.LogicalStatementType == LogicalStatementType_ELSIF)||
                    (TokenList[0].TokenValue.LogicalStatementType == LogicalStatementType_END_IF))
                {
                    //跳转行列号标记
                    UN_Param p;
                    p.nParm = nRunLineIndex;
                    pUint_Cmd->v_Param.push_back(p);
                    p.nParm = nRunCmdIndex;
                    pUint_Cmd->v_Param.push_back(p);
                }
            }

        }

    }
    return EX_RES::EX_RES_Done;
}

EX_RES RT_ScriptSystem::ActuatorUint_ELSE(ScriptUint_Cmd* pUint_Cmd)
{

    return EX_RES::EX_RES_Done;
}
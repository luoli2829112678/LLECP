#include"RT_Script.h"
RT_ScriptSystem::RT_ScriptSystem(/* args */)
{
    m_sLogicalStatement.emplace(sCmd_IF,        LogicalStatementType_IF);
    m_sLogicalStatement.emplace(sCmd_ELSE,      LogicalStatementType_ELSE);
    m_sLogicalStatement.emplace(sCmd_THEN,      LogicalStatementType_THEN);
    m_sLogicalStatement.emplace(sCmd_FOR,       LogicalStatementType_FOR);
    m_sLogicalStatement.emplace(sCmd_DO,        LogicalStatementType_DO);
    m_sLogicalStatement.emplace(sCmd_BY,        LogicalStatementType_BY);
    m_sLogicalStatement.emplace(sCmd_END_IF,    LogicalStatementType_END_IF);
    m_sLogicalStatement.emplace(sCmd_END_FOR,   LogicalStatementType_END_FOR);
    m_sLogicalStatement.emplace(sCmd_WHILE,     LogicalStatementType_WHILE);
    m_sLogicalStatement.emplace(sCmd_END_WHILE, LogicalStatementType_END_WHILE);
    m_sLogicalStatement.emplace(sCmd_ELSIF,       LogicalStatementType_ELSIF);
    m_sLogicalStatement.emplace(sCmd_CASE,        LogicalStatementType_CASE);
    m_sLogicalStatement.emplace(sCmd_OF,          LogicalStatementType_OF);
    m_sLogicalStatement.emplace(sCmd_END_CASE,    LogicalStatementType_END_CASE);
    m_sLogicalStatement.emplace(sCmd_TO,          LogicalStatementType_TO);
    m_sLogicalStatement.emplace(sCmd_REPEAT,      LogicalStatementType_REPEAT);
    m_sLogicalStatement.emplace(sCmd_UNTIL,       LogicalStatementType_UNTIL);
    m_sLogicalStatement.emplace(sCmd_END_REPEAT,  LogicalStatementType_END_REPEAT);
    m_sLogicalStatement.emplace(sCmd_EXIT,        LogicalStatementType_EXIT);
    m_sLogicalStatement.emplace(sCmd_RETURN,      LogicalStatementType_RETURN);

    m_sOperator.emplace(sOp_PLUS,   EN_OperatorType::OperatorType_PLUS);
    m_sOperator.emplace(sOp_MINUS,  EN_OperatorType::OperatorType_Subtract);
    m_sOperator.emplace(sOp_MUL,    EN_OperatorType::OperatorType_Ride);
    m_sOperator.emplace(sOp_DIV,    EN_OperatorType::OperatorType_Division);
    m_sOperator.emplace(sOp_GT,     EN_OperatorType::OperatorType_Greater);
    m_sOperator.emplace(sOp_LT,     EN_OperatorType::OperatorType_Less);
    m_sOperator.emplace(sOp_EQ,     EN_OperatorType::OperatorType_Equal);
    m_sOperator.emplace(sOp_NE,     EN_OperatorType::OperatorType_Unequal);
    m_sOperator.emplace(sOp_LE,     EN_OperatorType::OperatorType_LessEqual);
    m_sOperator.emplace(sOp_GE,     EN_OperatorType::OperatorType_GreaterEqual);
    //赋值单独拎出来
    //m_sOperator.emplace(sOp_ASSIGN,     EN_OperatorType::OperatorType_ASSIGN);

    m_sVariableType.emplace(s_BOOL,     EN_VariableType::en_BOOL);
    m_sVariableType.emplace(s_UINT32,     EN_VariableType::en_UINT32);
    m_sVariableType.emplace(s_INT32,     EN_VariableType::en_INT32);
    m_sVariableType.emplace(s_DOUBLE,     EN_VariableType::en_DOUBLE_64);
    m_sVariableType.emplace(s_STRING,     EN_VariableType::en_STRING);

    m_sDelimiter.emplace(s_Parentheses_L, EN_DelimiterType::DelimiterType_Parentheses_L);
    m_sDelimiter.emplace(s_Parentheses_R, EN_DelimiterType::DelimiterType_Parentheses_R);
    m_sDelimiter.emplace(s_Bracket_L,     EN_DelimiterType::DelimiterType_Bracket_L);
    m_sDelimiter.emplace(s_Bracket_R,     EN_DelimiterType::DelimiterType_Bracket_R);
    m_sDelimiter.emplace(s_Braces_L,      EN_DelimiterType::DelimiterType_Braces_L);
    m_sDelimiter.emplace(s_Braces_R,      EN_DelimiterType::DelimiterType_Braces_R);
    m_sDelimiter.emplace(s_BracketA_L,    EN_DelimiterType::DelimiterType_BracketA_L);
    m_sDelimiter.emplace(s_BracketA_R,    EN_DelimiterType::DelimiterType_BracketA_R);

}

RT_ScriptSystem::~RT_ScriptSystem()
{
    
}


int RT_ScriptSystem::InitRT_ScriptSystem()
{
    //清空数据
    nPushBufferIndex = 0;
    nPushLineIndex = 0;
    //清空buffer
    for (int i = 0;i < SCRIPTNUMBUFF_MAX;i++)
    {
        ScripList[i].InitScript();
    }
    printf("InitRT_Script()\n");
    return 0;
}
int RT_ScriptSystem::PushScriptCmd(ScriptUint_Cmd Cmd)
{
    return ScripList[nPushBufferIndex].PushCmd(Cmd);
}
int RT_ScriptSystem::PushScriptCmd(std::string sCmd)
{
    ScripList[nPushBufferIndex].bEnable = true; 
    int nRet = 0;
    ScriptUint_Cmd Cmd = RT_ScriptInterpreter(sCmd,nRet);
    //如果返回1就是变量声明类不需要push
    if (nRet!=0)
        return nRet;
    return PushScriptCmd(Cmd);
}
int RT_ScriptSystem::PushScriptCmdFinish()
{
    return 0;
}
int RT_ScriptSystem::PushLineBreak()
{
    ScripList[nPushBufferIndex].PushLineBreak();
    nPushLineIndex ++;
    return 0;
}
int RT_ScriptSystem::PushBufferBreak()
{
    nPushBufferIndex ++;
    return 0;
}

int RT_ScriptSystem::StartRT_Script()
{
    for (int i = 0;i < SCRIPTNUMBUFF_MAX;i++)
    {
        ScripList[i].ResetScript();
    }
    m_StartScritp  = true;
    return 0;
}
int RT_ScriptSystem::StopRT_Script()
{
    return 0;
}
int RT_ScriptSystem::ResetRT_Script()
{
    return 0;
}

void RT_ScriptSystem::RT_ScriptTick()
{
    if(m_StartScritp)
    {
        for(nRunBufferIndex = 0;nRunBufferIndex<SCRIPTNUMBUFF_MAX;nRunBufferIndex++)
        {
            if(ScripList[nRunBufferIndex].bEnable)
            {
                EX_RES res = RT_ScriptActuator(ScripList[nRunBufferIndex].GetRunLine());
                if(EX_RES_Done == res)
                {
                    ScripList[nRunBufferIndex].CmdRunDone();
                }
            }
        }
        bool bRunDone = true;
        for(nRunBufferIndex = 0;nRunBufferIndex<SCRIPTNUMBUFF_MAX;nRunBufferIndex++)
        {
            if((!ScripList[nRunBufferIndex].BufferRunFinsh())&&ScripList[nRunBufferIndex].bEnable)
            {
                bRunDone = false;
            }
        }
        if(bRunDone)
        {
            m_StartScritp = false;
        }
    }
}
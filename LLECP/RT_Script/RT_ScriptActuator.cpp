#include"RT_Script.h"
EX_RES RT_ScriptSystem::RT_ScriptActuator(ScriptUint_Cmd* pUint_Cmd)
{

    //检测到第一个元素为逻辑指令，那么该指令就为逻辑指令，需要丢到对应的逻辑指令内执行
    if(pUint_Cmd->v_Token[0].TokenType == TokenType_LogicalStatement)
    {
        switch (pUint_Cmd->v_Token[0].TokenValue.LogicalStatementType)
        {
        case LogicalStatementType_IF :
                return ActuatorUint_IF(pUint_Cmd);
            break;
        
        default:
            break;
        }
    }

    //检测第二个元素为赋值，那么该指令为赋值指令
    if(pUint_Cmd->v_Token[1].TokenType == TokenType_Assignment)
    {
        std::vector<ScriptUint_Token> c_Token(pUint_Cmd->v_Token.begin() + 2, pUint_Cmd->v_Token.end());
        double outVar = RT_ScriptCalculator(c_Token);
        //全局变量
        if(-1 == pUint_Cmd->v_Token[0].nRemarks)
        {
            auto it = m_ScriptVariableGlobal.begin();
            //移动迭代器
            std::advance(it, pUint_Cmd->v_Token[0].TokenValue.KeywordAddr);
            if (it != m_ScriptVariableGlobal.end())
            {
                it->second.SetVariable(outVar);
            }
        }
        //buffer变量
        else
        {
            auto it = m_ScriptVariableBuffer[pUint_Cmd->v_Token[0].nRemarks].begin();
            //移动迭代器
            std::advance(it, pUint_Cmd->v_Token[0].TokenValue.KeywordAddr);
            if (it != m_ScriptVariableBuffer[pUint_Cmd->v_Token[0].nRemarks].end())
            {
                it->second.SetVariable(outVar);
            }
        }
        return EX_RES_Done;
    }

    return EX_RES_Error;
}


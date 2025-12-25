#include"CmdUint.h"

CmdUint::CmdUint()
{

}

CmdUint::~CmdUint()
{
}

int CmdUint::SetCmdUint(std::vector<BaseToken> vToken)
{
    m_bIsCmdInit = false;
    m_enCmdType = CmdType_NULL;
    m_vToken = vToken;
    return 0;
}
std::vector<BaseToken>* CmdUint::GetToken()
{
    return &m_vToken;
}
int CmdUint::SetCmdState(std::vector<UN_TransitionParam>v_State)
{
    m_vState  = v_State;
    return 0;
}
std::vector<UN_TransitionParam>* CmdUint::GetCmdState()
{
    return &m_vState;
}
int CmdUint::SetCmdParam(std::vector<UN_TransitionParam>v_Param)
{
    m_vParam = v_Param;
    return 0;
}
std::vector<UN_TransitionParam>* CmdUint::GetCmdParam()
{
    return &m_vParam;
}

int CmdUint::InitCmd()
{
    InitCmdType();
    m_bIsCmdInit = true;
    return 0;
}
bool CmdUint::IsInitCmd()
{
    return m_bIsCmdInit;
}

EN_CmdType CmdUint::GetCmdType()
{
    return m_enCmdType;
}

int CmdUint::ResetCmd()
{
    m_vState.clear();
    return 0;
}

int CmdUint::SetResult(ST_Result stResult)
{
    m_stResult = stResult;
    return 0;
}

ST_Result CmdUint::GetResult()
{
    return m_stResult;
}

int CmdUint::InitCmdType()
{
    for (size_t i = 0; i < m_vToken.size(); i++)
    {
        if(m_vToken[i].enTokenType == TokenType_LogicalStatement)
        {
            //逻辑语句
            switch(static_cast<EN_LogicalStatementType>(static_cast<int>(m_vToken[i].KeywordAddr)))
            {
                case LogicalStatementType_IF:
                    m_enCmdType = CmdType_IF;
                    break;
                case LogicalStatementType_ELSIF:
                    m_enCmdType = CmdType_ELSEIF;
                    break;
                case LogicalStatementType_ELSE:
                    m_enCmdType = CmdType_ELSE;
                    break;
                case LogicalStatementType_END_IF:
                    m_enCmdType = CmdType_ENDIF;
                    break;
                case LogicalStatementType_WHILE:
                    m_enCmdType = CmdType_WHILE;
                    break;
                case LogicalStatementType_END_WHILE:
                    m_enCmdType = CmdType_ENDWHILE;
                    break;
                case LogicalStatementType_LOOP:
                    m_enCmdType = CmdType_LOOP;
                    break;
                case LogicalStatementType_END_LOOP:
                    m_enCmdType = CmdType_ENDLOOP;
                    break;
                default:
                    printf("Error: CmdUint::InitCmdType failed to init cmd type!\n");
                    return -1;
                    break;
            }
            return 0;
        }
        else if(m_vToken[i].enTokenType == TokenType_Assignment)
        {
            m_enCmdType = CmdType_Assignment;
            return 0;
        }
        else if(m_vToken[i].enTokenType == TokenType_VariableType)
        {
            m_enCmdType = CmdType_VariableDeclaration;
            return 0;
        }
        else if(m_vToken[i].enTokenType == TokenType_Function)
        {
            m_enCmdType = CmdType_Function;
            return 0;
        }
    }
    if(m_enCmdType == CmdType_NULL)
    {
        printf("Error: CmdUint::InitCmdType failed to init cmd type!\n");
        return -1;
    }
    return 0;
}
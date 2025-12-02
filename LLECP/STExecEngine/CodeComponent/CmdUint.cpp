#include"CmdUint.h"

CmdUint::CmdUint()
{

}

CmdUint::~CmdUint()
{
}

int CmdUint::SetCmdUint(std::vector<BaseToken> vToken)
{
    m_vToken = vToken;
    return 0;
}
std::vector<BaseToken> CmdUint::GetToken()
{
    return m_vToken;
}
int CmdUint::SetCmdState(std::vector<VariableUint>v_State)
{
    m_vState  = v_State;
    return 0;
}
std::vector<VariableUint> CmdUint::GetCmdState()
{
    return m_vState;
}
int CmdUint::SetCmdParam(std::vector<VariableUint>v_Param)
{
    m_vParam = v_Param;
    return 0;
}
std::vector<VariableUint> CmdUint::GetCmdParam()
{
    return m_vParam;
}

int CmdUint::InitCmd()
{
    m_bIsCmdInit = true;
    return 0;
}
bool CmdUint::IsInitCmd()
{
    return m_bIsCmdInit;
}
int CmdUint::SetCmdRunDone()
{
    m_bCmdRunDone = true;
    return 0;
}
bool CmdUint::IsCmdRunDone()
{
    return m_bCmdRunDone;
}

int CmdUint::ResetCmd()
{
    m_vState.clear();
    m_bCmdRunDone = false;
    return 0;
}
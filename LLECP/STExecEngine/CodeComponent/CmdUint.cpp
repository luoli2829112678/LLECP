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
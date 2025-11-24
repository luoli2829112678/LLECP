#include"LineUint.h"

LineUint::LineUint(/* args */)
{
}

LineUint::~LineUint()
{
}

int LineUint::PushCmd(CmdUint cmd)
{
    m_vCmd.push_back(cmd);
    return 0;
}
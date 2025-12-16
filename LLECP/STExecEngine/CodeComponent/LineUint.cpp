#include"LineUint.h"

LineUint::LineUint(/* args */)
{
    nCmdNum_Now = 0;
    nCmdRunIndex = 0;
    bLineRunDone = false;
}

LineUint::~LineUint()
{
}

int LineUint::PushCmd(CmdUint cmd)
{
    m_vCmd.push_back(cmd);
    return 0;
}
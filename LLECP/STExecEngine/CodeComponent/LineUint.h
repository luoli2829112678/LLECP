
#pragma once
#include"CmdUint.h"
class LineUint
{
public:
    uint32_t nCmdNum_Now;
    uint32_t nCmdRunIndex;
    bool bLineRunDone = false;
    std::vector<CmdUint> m_vCmd;
public:
    LineUint(/* args */);
    ~LineUint();

    int PushCmd(CmdUint cmd);
};


#pragma once
#include"CmdUint.h"
class LineUint
{
public:
    uint32_t nCmdNum_Now;
    uint32_t nCmdRunIndex;
    bool bLineRunDone;
    std::vector<CmdUint> m_vCmd;
    //执行后是否跳转
    ST_Result m_stResult;
    //执行后跳转目标位置
public:
    LineUint(/* args */);
    ~LineUint();

    int PushCmd(CmdUint cmd);
};

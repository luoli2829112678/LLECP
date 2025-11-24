#pragma once
#include"LineUint.h"
class BufferUint
{
private:

    uint32_t m_nLineRunIndex;

    bool m_bBufferRunDone=false;
    std::vector<LineUint> m_vLineList;
    bool m_bBuffEnable;
public:
    BufferUint(/* args */);
    ~BufferUint();


    int EnableBuffer(bool bEnable);
    bool IsEnable();
    int CleanBuffer();
    int StartPushLine();
    int PushCmd(uint16_t nLineID,CmdUint cmd);
};


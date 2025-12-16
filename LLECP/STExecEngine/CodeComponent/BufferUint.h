#pragma once
#include"LineUint.h"
class BufferUint
{
    
public:
    uint32_t m_nLineRunIndex;

    bool m_bBufferRunDone=false;
    std::vector<LineUint> m_vLineList;
    bool m_bBuffEnable;
public:
    BufferUint(/* args */);
    ~BufferUint();


    int EnableBuffer(bool bEnable);
    int CleanBuffer();
    int StartPushLine();
    int PushCmd(uint16_t nLineID,CmdUint cmd);

    //小蝌蚪找妈妈
    int InitBuffer();
    int InitCmdType();
    int StatementMatching();
};


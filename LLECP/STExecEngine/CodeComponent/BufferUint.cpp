#include"BufferUint.h"

BufferUint::BufferUint(/* args */)
{
    uint32_t m_nLineRunIndex = -1;
}

BufferUint::~BufferUint()
{
}


int BufferUint::EnableBuffer(bool bEnable)
{
    m_bBuffEnable = bEnable;
    return 0;
}

int BufferUint::CleanBuffer()
{
    m_nLineRunIndex = -1;

    m_bBufferRunDone=false;
    m_vLineList.clear();
    return 0;
}

bool BufferUint::IsEnable()
{
    return m_bBuffEnable;
}

int BufferUint::StartPushLine()
{
    //新增一行
    LineUint T_LineUint;
    m_vLineList.push_back(T_LineUint);
    return 0;
}

int BufferUint::PushCmd(uint16_t nLineID,CmdUint cmd)
{
    return m_vLineList.back().PushCmd(cmd);
}


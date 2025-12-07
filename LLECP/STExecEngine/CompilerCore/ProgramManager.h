#pragma once
#include"./CodeComponent/BufferUint.h"
class ProgramManager
{
private:
    BufferUint m_BufferUint[64];

    uint16_t m_PushBufferID;
    uint16_t m_PushLineID;
public:
    ProgramManager(/* args */);
    ~ProgramManager();

    int EnableBuffer(uint16_t nBufferID,bool bEnable);

    int ClearProgram();
    int StartPushBuffer();
    int StartPushLine();
    int PushCmd(CmdUint sCmd);
    //初始化buffer
    int InitBuffer(BufferUint* pBufferUint);
};



#pragma once
#include"./CodeComponent/BufferUint.h"
class ProgramManager
{
public:
    BufferUint m_BufferUint[64];

    uint16_t m_PushBufferID;
    uint16_t m_PushLineID;
    bool m_bProgramRunDone;
public:
    ProgramManager(/* args */);
    ~ProgramManager();

    int EnableBuffer(uint16_t nBufferID,bool bEnable);

    int ClearProgram();
    int StartPushBuffer();
    int StartPushLine();
    int PushCmd(CmdUint sCmd);
    //初始化buffer//if等找妈妈
    int InitBuffer(int nBufferID);

};



#include"ProgramManager.h"

ProgramManager::ProgramManager(/* args */)
{
    m_PushLineID = -1;
    m_PushBufferID = -1;
}

ProgramManager::~ProgramManager()
{
}

int ProgramManager::ClearProgram()
{
    for (size_t i = 0; i < 64; i++)
    {
        m_BufferUint[i].CleanBuffer();
    }
    return 0;
}

int ProgramManager::EnableBuffer(uint16_t nBufferID,bool bEnable)
{
    return m_BufferUint[nBufferID].EnableBuffer(bEnable);
}

int ProgramManager::StartPushBuffer()
{
    //最多64个buffer
    m_PushBufferID ++;
    if(64 == m_PushBufferID)
    {
        m_PushBufferID -- ;
        return -1;
    }
    m_PushLineID = -1;
    return 0;
}

int ProgramManager::StartPushLine()
{
    //buffer行数不做限制
    m_BufferUint[m_PushBufferID].StartPushLine();
    m_PushLineID ++;
    return 0;
}

int ProgramManager::PushCmd(CmdUint Cmd)
{
    return m_BufferUint[m_PushBufferID].PushCmd(m_PushLineID,Cmd);
}
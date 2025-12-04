#include"STExecEngine.h"
STExecEngine::STExecEngine(/* args */)
    : m_StructManager()              
    , m_VariableManager(&m_StructManager)  
{

    m_nPushBufferID = -1;
    m_pParser = new Parser();
    m_pActuator = new Actuator(&m_VariableManager,&m_StructManager,&m_FunctionManager);
}

STExecEngine::~STExecEngine()
{

}


int STExecEngine::STEE_EnableBuffer(uint16_t nBufferID,bool bEnable)
{
    if(nBufferID>63)
        return -1;
    return m_ProgramManager.EnableBuffer(nBufferID,bEnable);
}

int STExecEngine::STEE_StartPushBuffer()
{
    m_nPushBufferID ++;
    m_VariableManager.SetPushBufferID(m_nPushBufferID);
    return m_ProgramManager.StartPushBuffer();
}

int STExecEngine::STEE_StartPushLine()
{
    return m_ProgramManager.StartPushLine();
}

int STExecEngine::STEE_PushCmd(string scmd)
{
    return 0;
}
#include"STExecEngine.h"
STExecEngine::STExecEngine(/* args */)
    : m_StructManager()              
    , m_VariableManager(&m_StructManager)  
{
    m_ProgramManager = ProgramManager();
    m_nPushBufferID = -1;
    m_pParser = new Parser(&m_VariableManager,&m_StructManager,&m_FunctionManager);
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
    CmdUint T_CmdUint;
    int res =  m_pParser->ParserCmd(m_nPushBufferID,scmd,T_CmdUint);
    if(0 == res)
    {
        m_ProgramManager.PushCmd(T_CmdUint);
    }
    return res;
}
int STExecEngine::InitProgramManager()
{
    m_ProgramManager.m_bProgramRunDone = false;
    for (size_t i = 0; i < m_nPushBufferID + 1; i++)
    {
        m_ProgramManager.InitBuffer(i);
    }
    return 0;
}

int STExecEngine::ExecuteProgram()
{
    for (size_t i = 0; i <= m_ProgramManager.m_PushBufferID; i++)
    {
        if(m_ProgramManager.m_BufferUint[i].m_bBuffEnable && !m_ProgramManager.m_BufferUint[i].m_bBufferRunDone)
        {
            uint32_t* pRunLine = &m_ProgramManager.m_BufferUint[i].m_nLineRunIndex;
            uint32_t* pRunCmd = &m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].nCmdRunIndex;
            for (;*pRunLine < m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].m_vCmd.size();)
            {
                CmdUint RunCmd = m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].m_vCmd[*pRunCmd];
                m_pActuator->ExecuteCommand(RunCmd);
                ST_Result CmdResult = RunCmd.GetResult();
                if(CmdResult.bIsJump)
                {
                    m_ProgramManager.m_BufferUint[i].m_nLineRunIndex = CmdResult.nJumpLinePos;
                    m_ProgramManager.m_BufferUint[i].m_vLineList[CmdResult.nJumpLinePos].nCmdRunIndex = CmdResult.nJumpCmdPos;
                    continue;
                }
                
                //BUFFER 跳出
                if(!CmdResult.bIsNextCmd)
                {
                    break;
                }
                else
                {
                    //行最后一句执行完成
                    if(*pRunLine == m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].m_vCmd.size()-1)
                    {
                        //判断是否为最后一行
                        if(*pRunLine == m_ProgramManager.m_BufferUint[i].m_vLineList.size()-1)
                        {
                            //最后一行
                            m_ProgramManager.m_BufferUint[i].m_bBufferRunDone = true;
                            //判断工程是否执行完成
                            for( size_t j = 0; j <= m_ProgramManager.m_PushBufferID; j++)
                            {
                                if(m_ProgramManager.m_BufferUint[j].m_bBuffEnable && !m_ProgramManager.m_BufferUint[j].m_bBufferRunDone)
                                {
                                    break;
                                }
                                if(j == m_ProgramManager.m_PushBufferID)
                                {
                                    //所有buffer执行完成
                                    m_ProgramManager.m_bProgramRunDone = true;
                                    printf("ExecuteProgram:All Program Execute Done!\n");
                                }
                            }
                            break;
                        }
                        //行结束
                        m_ProgramManager.m_BufferUint[i].m_nLineRunIndex++;
                        m_ProgramManager.m_BufferUint[i].m_vLineList[m_ProgramManager.m_BufferUint[i].m_nLineRunIndex].nCmdRunIndex = 0;
                    }
                    else
                    {
                        m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].nCmdRunIndex++;
                    }
                }

            }
        }
    }
    return 0;
}
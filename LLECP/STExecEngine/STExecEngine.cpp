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


void PrintNowUs()
{
    using namespace std::chrono;

    // 当前系统时间
    auto now = system_clock::now();

    // 秒级时间点
    auto sec = time_point_cast<seconds>(now);

    // 微秒部分
    auto us = duration_cast<microseconds>(now - sec).count();

    // 转为本地时间
    std::time_t tt = system_clock::to_time_t(sec);
    std::tm tm{};
    localtime_r(&tt, &tm);   // Linux 推荐，线程安全
    // Windows 用 localtime_s(&tm, &tt);

    printf("%04d-%02d-%02d %02d:%02d:%02d.%06ld\n",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        us);
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
            for (;*pRunCmd < m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].m_vCmd.size();)
            {
                // auto start = std::chrono::steady_clock::now();
                CmdUint RunCmd = m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].m_vCmd[*pRunCmd];
                m_pActuator->ExecuteCommand(RunCmd);
                // auto end = std::chrono::steady_clock::now();
                // auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                // printf("Buffer %zu Line %u Cmd %u 执行时间1: %ld us\n", i, *pRunLine, *pRunCmd, us);
                ST_Result CmdResult = RunCmd.GetResult();
                //if执行完成后面的else/elseif跳转 该if 的if elseif else 状态全部为1
                if((!CmdResult.bIsJump)&&(RunCmd.GetCmdType() == CmdType_IF || RunCmd.GetCmdType() == CmdType_ELSEIF))
                {
                    std::vector<UN_TransitionParam>* pvCmdParam = RunCmd.GetCmdParam();
                    while(pvCmdParam->size()>=2)
                    {
                        int nJumpLine = pvCmdParam->at(0).nParam;
                        int nJumpCmd  = pvCmdParam->at(1).nParam;
                        UN_TransitionParam CmdParam;
                        CmdParam.nParam = 1;
                        vector<UN_TransitionParam>*p_vTCmdParam = m_ProgramManager.m_BufferUint[i].m_vLineList[nJumpLine].m_vCmd[nJumpCmd].GetCmdState();
                        if(p_vTCmdParam->size() > 0)//end_if不需要
                        {
                            p_vTCmdParam->at(0) = CmdParam;
                            m_ProgramManager.m_BufferUint[i].m_vLineList[nJumpLine].m_vCmd[nJumpCmd].SetCmdState(*p_vTCmdParam);
                            
                        }
                        //拿出下一个节点
                        pvCmdParam = m_ProgramManager.m_BufferUint[i].m_vLineList[nJumpLine].m_vCmd[nJumpCmd].GetCmdParam();
                    }
                }
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
                    if(*pRunCmd == m_ProgramManager.m_BufferUint[i].m_vLineList[*pRunLine].m_vCmd.size()-1)
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
                                    break;
                                }
                            }
                            break;
                        }
                        //行结束
                        m_ProgramManager.m_BufferUint[i].m_nLineRunIndex++;
                        m_ProgramManager.m_BufferUint[i].m_vLineList[m_ProgramManager.m_BufferUint[i].m_nLineRunIndex].nCmdRunIndex = 0;
                        return 0;
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
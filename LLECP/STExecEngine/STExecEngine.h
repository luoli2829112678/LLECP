#include"VariableUint/StructManager.h"
#include"CompilerCore/Parser.h"
#include"CompilerCore/Actuator.h"
#include"CompilerCore/VariableManager.h"
#include"CompilerCore/FunctionManager.h"
#include"CompilerCore/ProgramManager.h"
class STExecEngine
{
public:
    //用户定义的结构体
    StructManager m_StructManager;
    //变量管理器
    VariableManager m_VariableManager;
    //函数管理器
    FunctionManager m_FunctionManager;
    //程序管理器
    ProgramManager m_ProgramManager;
    //解析器
    Parser* m_pParser;
    //执行器
    Actuator* m_pActuator;
    //
    int m_nPushBufferID;
public:
    STExecEngine(/* args */);
    ~STExecEngine();

    int STEE_EnableBuffer(uint16_t nBufferID,bool bEnable);
    //buffer切换
    int STEE_StartPushBuffer();
    //行切换
    int STEE_StartPushLine();
    //push指令
    int STEE_PushCmd(string scmd);
};

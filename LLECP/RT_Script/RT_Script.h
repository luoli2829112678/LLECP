#include<string>
#include<map>
#include"ScriptVariable.h"
#include"ScriptUint/ScriptUint_Buffer.h"
#include"ScriptDefine.h"
#include"sCmdNameDefine.h"
//#include"HRC_Rbt.h"
//通过#define HRCRbt HRC_Rbt::instance()使用HRC_Rbt函数
#define SCRIPTNUMBUFF_MAX 64



class RT_ScriptSystem
{
private:
    bool m_StartScritp;
    ScriptUint_Buffer ScripList[SCRIPTNUMBUFF_MAX];
    //当前push的bufferIndex
    uint32_t nPushBufferIndex;
    //当前push的LineIndex
    uint32_t nPushLineIndex;
    //runIndex
    uint32_t nRunBufferIndex;
    uint32_t nRunLineIndex;
    uint32_t nRunCmdIndex;
    //逻辑语句
    std::map<std::string, EN_LogicalStatementType> m_sLogicalStatement;
    //运算符
    std::map<std::string, EN_OperatorType> m_sOperator;
    //数据类型
    std::map<std::string, EN_VariableType> m_sVariableType;
    //分隔符
    std::map<std::string, EN_DelimiterType> m_sDelimiter;
    //变量
    std::map<std::string, ScriptVariable> m_ScriptVariableGlobal;
    std::map<std::string, ScriptVariable> m_ScriptVariableBuffer[SCRIPTNUMBUFF_MAX];

public:

    RT_ScriptSystem(/* args */);
    ~RT_ScriptSystem();


    //队列结构
    int InitRT_ScriptSystem();
    int PushScriptCmd(std::string sCmd);
    int PushScriptCmdFinish();
    int PushLineBreak();
    int PushBufferBreak();
    int StartRT_Script();
    int StopRT_Script();
    //实时调用
    void RT_ScriptTick();
//private:
    //执行器
    EX_RES RT_ScriptActuator(ScriptUint_Cmd* pUint_Cmd);
    //逻辑执行单元
    EX_RES ActuatorUint_IF(ScriptUint_Cmd* pUint_Cmd);
    EX_RES ActuatorUint_ELSE(ScriptUint_Cmd* pUint_Cmd);

    //解释器
    ScriptUint_Cmd RT_ScriptInterpreter(std::string sCmd,int& nRet);
    ScriptUint_Token AnalysisToken_Operator(std::string sToken);
    ScriptUint_Token AnalysisToken_Variable(std::string sToken);
    ScriptUint_Token AnalysisToken_LogicalStatement(std::string sToken);
    ScriptUint_Token AnalysisToken_VariableType(std::string sToken);
    ScriptUint_Token AnalysisToken_Function(std::string sToken);
    ScriptUint_Token AnalysisToken_Delimiter(std::string sToken);

    //计算器
    double RT_ScriptCalculator(std::vector<ScriptUint_Token>v_Token);

private:
    int ResetRT_Script();
    int PushScriptCmd(ScriptUint_Cmd Cmd);


    int VariableDeclaratio(int16_t bufferindex,std::string sVarName, ScriptVariable var);
    bool IsOperator(const char c);
    bool IsVariable(const char c);
    EN_VariableType IsVariableType(std::string str);
    bool IsCharacter(const char c);
    bool IsNumber(const char c);
};

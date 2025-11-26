#include"ScriptUint_Cmd.h"
class ScriptUint_Line
{
private:
    uint32_t nCmdNum_Max;
    uint32_t nCmdNum_Now;
    uint32_t nCmdRunIndex;
    bool bLineRunDone = false;

    std::vector<ScriptUint_Cmd> v_CmdList;
    friend class RT_ScriptSystem;
public:
    ScriptUint_Line();
    ~ScriptUint_Line();
    int Reset();
    int GetCmdNUm();
    int GetCmdRunIndex();
    int PushCmd(ScriptUint_Cmd sCmd);
    ScriptUint_Cmd* GetRunCmd();
    int CmdRunDone();
};
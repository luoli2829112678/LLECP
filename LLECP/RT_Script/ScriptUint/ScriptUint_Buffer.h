#pragma once
#include"ScriptUint_Line.h"
class ScriptUint_Buffer
{
private:
    const uint32_t nLineNum_Max = 999;
    uint32_t nLineNum_Now;
    uint32_t nLineRunIndex;
    bool bBufferRunDone=false;
    std::vector<ScriptUint_Line> v_LineList;
    friend class RT_ScriptSystem;
public:
    bool bEnable;
    ScriptUint_Buffer();
    ~ScriptUint_Buffer();
    int InitScript();
    int ResetScript();
    int PushCmd(ScriptUint_Cmd scmd);
    //换行新增一行
    int PushLineBreak();
    int GetLineNum();
    int GetLineRunIndex();
    ScriptUint_Cmd* GetRunLine();
    int CmdRunDone();
    bool BufferRunFinsh();
};
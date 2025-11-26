#include"ScriptUint_Line.h"

ScriptUint_Line::ScriptUint_Line()
{
    nCmdNum_Max = 999;
    nCmdNum_Now = 0;
    nCmdRunIndex = 0;
}

ScriptUint_Line::~ScriptUint_Line()
{

}

int ScriptUint_Line::Reset()
{
    for(int i=0;i<v_CmdList.size();i++)
    {
        v_CmdList[i].ResetCommand();
    }
    nCmdRunIndex = 0;
    bLineRunDone = false;
    return 0;
}
int ScriptUint_Line::PushCmd(ScriptUint_Cmd scmd)
{
    if (nCmdNum_Now == nCmdNum_Max)
    {
        return -1;
    }
    v_CmdList.push_back(scmd);
    nCmdNum_Now ++;
    return 0;
}
int ScriptUint_Line::GetCmdNUm()
{
    return nCmdNum_Now;
}
int ScriptUint_Line::GetCmdRunIndex()
{
    return nCmdRunIndex;
}

ScriptUint_Cmd* ScriptUint_Line::GetRunCmd()
{
    return &v_CmdList[nCmdRunIndex];
}

int ScriptUint_Line::CmdRunDone()
{
    v_CmdList[nCmdRunIndex].CmdRunDone();
    nCmdRunIndex ++;
    if(nCmdRunIndex==nCmdNum_Now)
    {
        bLineRunDone = true;
        return 1;
    }
    return 0;
}
#include"ScriptUint_Buffer.h"

ScriptUint_Buffer::ScriptUint_Buffer()
{
    //脚本默认带第一行读取到换行后新加一行
    ScriptUint_Line firstline;
    v_LineList.push_back(firstline);
}

ScriptUint_Buffer::~ScriptUint_Buffer()
{

}

int ScriptUint_Buffer::InitScript()
{
    for(int i = 0;i<v_LineList.size();i++)
    {
        //清空指令
        v_LineList.clear();
        //清空内存
        std::vector<ScriptUint_Line>().swap(v_LineList);
        //脚本默认带第一行读取到换行后新加一行
        ScriptUint_Line firstline;
        v_LineList.push_back(firstline);
    }
    return 0;
}
int ScriptUint_Buffer::ResetScript()
{
    for(int i = 0;i<v_LineList.size();i++)
    {
        v_LineList[i].Reset();
    }
    nLineRunIndex = 0;
    bBufferRunDone = false;
    return 0;
}

int ScriptUint_Buffer::PushCmd(ScriptUint_Cmd cmd)
{
    return v_LineList[nLineNum_Now].PushCmd(cmd);
}

int ScriptUint_Buffer::PushLineBreak()
{
    if (nLineNum_Now == nLineNum_Max)
    return -1;
    //读取到换行插入一行
    ScriptUint_Line line;
    v_LineList.push_back(line);
    nLineNum_Now++;
    return 0;
}
int ScriptUint_Buffer::GetLineNum()
{
    return nLineNum_Now;
}

ScriptUint_Cmd* ScriptUint_Buffer::GetRunLine()
{
    return v_LineList[nLineRunIndex].GetRunCmd();
}
int ScriptUint_Buffer::CmdRunDone()
{
    if(1 ==v_LineList[nLineRunIndex].CmdRunDone())
    {
        nLineRunIndex ++;
    }
    if(nLineRunIndex > nLineNum_Now)
        bBufferRunDone = true;
    return 0;
}

int ScriptUint_Buffer::GetLineRunIndex()
{
    return nLineRunIndex;
}

bool ScriptUint_Buffer::BufferRunFinsh()
{
    return bBufferRunDone;
}
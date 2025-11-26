#include"ScriptUint_Cmd.h"
ScriptUint_Cmd::ScriptUint_Cmd()
{

}
ScriptUint_Cmd::~ScriptUint_Cmd()
{
    
}

int ScriptUint_Cmd::ResetCommand()
{
    v_State.clear();
    bCmdRunDone = false;
    return 0;
}

int ScriptUint_Cmd::CmdRunDone()
{
    bCmdRunDone = true;
    return 0;
}

EN_CmdType ScriptUint_Cmd::GetCmdType()
{
    return stCmdType;
}
int ScriptUint_Cmd::SetCmdType(EN_CmdType setCmdType)
{
    stCmdType = setCmdType;
    return 0;
}
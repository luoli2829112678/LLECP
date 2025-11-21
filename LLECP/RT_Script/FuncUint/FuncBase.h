#pragma once
#include"../ScriptUint/ScriptUint_Buffer.h"
#include"../ScriptVariable.h"
#include<map>
class FuncBase
{
private:
    std::string sFuncName;
    std::map<std::string, ScriptVariable> m_ScriptVariableFunc;
    std::vector<ScriptUint_Cmd> v_CmdList;
public:
    FuncBase(/* args */);
    ~FuncBase();
};


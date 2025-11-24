#pragma once
#include"BaseToken.h"
#include"../VariableUint/VariableUint.h"
#include<vector>
class CmdUint
{
private:
    std::vector<BaseToken> m_vToken;
    //记录while次数
    std::vector<VariableUint>v_State;
    //记录IF的else结束位置
    std::vector<VariableUint>v_Param;
    bool bIsInit = false;
    bool bCmdRunDone=false;
public:
    CmdUint();
    //push阶段
    int SetCmdUint(std::vector<BaseToken> vToken);
    ~CmdUint();
};

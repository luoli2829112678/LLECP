#pragma once
#include"BaseToken.h"
#include"../VariableUint/VariableUint.h"
#include<vector>
class CmdUint
{
private:
    std::vector<BaseToken> m_vToken;
    //记录while次数
    std::vector<VariableUint>m_vState;
    //记录IF的else结束位置
    std::vector<VariableUint>m_vParam;
    bool m_bIsCmdInit = false;
    bool m_bCmdRunDone=false;

    //执行后是否跳转

    //执行后跳转目标位置
    
public:
    CmdUint();
    //push阶段
    int SetCmdUint(std::vector<BaseToken> vToken);
    std::vector<BaseToken> GetToken();
    int SetCmdState(std::vector<VariableUint>v_State);
    std::vector<VariableUint> GetCmdState();
    int SetCmdParam(std::vector<VariableUint>v_Param);
    std::vector<VariableUint> GetCmdParam();

    int InitCmd();
    bool IsInitCmd();
    int SetCmdRunDone();
    bool IsCmdRunDone();

    int ResetCmd();
    ~CmdUint();
};

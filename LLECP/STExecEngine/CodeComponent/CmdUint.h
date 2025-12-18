#pragma once
#include"BaseToken.h"
#include"../VariableUint/VariableUint.h"
#include<vector>



class CmdUint
{
private:
    std::vector<BaseToken> m_vToken;
    //记录while次数
    std::vector<UN_TransitionParam>m_vState;

    //记录IF的else结束位置
    std::vector<UN_TransitionParam>m_vParam;
    //对于IF，m_vParam[0]为不满足的跳转行，m_vParam[1]为不满足的跳转cmd位置(elseif/else/end_if)



    bool m_bIsCmdInit;

    EN_CmdType m_enCmdType;
    //执行后是否跳转
    ST_Result m_stResult;
    //执行后跳转目标位置
    
public:
    CmdUint();
    EN_CmdType GetCmdType();
    //push阶段
    int SetCmdUint(std::vector<BaseToken> vToken);
    std::vector<BaseToken>* GetToken();
    int SetCmdState(std::vector<UN_TransitionParam>v_State);
    std::vector<UN_TransitionParam> GetCmdState();
    int SetCmdParam(std::vector<UN_TransitionParam>v_Param);
    std::vector<UN_TransitionParam> GetCmdParam();

    int InitCmd();
    int InitCmdType();
    bool IsInitCmd();


    int ResetCmd();
    int SetResult(ST_Result stResult);
    ST_Result GetResult();
    ~CmdUint();
};

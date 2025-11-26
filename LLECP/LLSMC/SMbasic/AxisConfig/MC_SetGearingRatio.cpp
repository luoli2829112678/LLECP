#include"MC_SetGearingRatio.h"
MC_SetGearingRatio::MC_SetGearingRatio(/* args */)
{
}

MC_SetGearingRatio::~MC_SetGearingRatio()
{
}

void MC_SetGearingRatio::operator()(CIA402Axis* axis)
{
    if(nullptr == axis)
    {
        return;
    }
    m_pCIA402Axis = axis;
}
void MC_SetGearingRatio::operator()(CIA402Axis* axis,bool bExecute,double dGearingRatio,bool& bDone,bool& bError,int& ErrorID)
{
    if(nullptr == axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    m_pCIA402Axis = axis;
    m_bExecute = bExecute;
    m_dGearingRatio = dGearingRatio;
    this->Execute();
    bDone = m_bDone;
    bError = m_bError;
    ErrorID = m_nErrorID;
}


void MC_SetGearingRatio::Execute()
{
    if(nullptr == m_pCIA402Axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    //输出初始化
    m_bDone             = false;
    m_bError            = false;
    m_nErrorID           = SMEC_SUCCESSED;
    int res = AEC_SUCCESSED;
    //上升沿push
    if(m_Timer.R_TRIG(m_bExecute))
    {
        res = m_pCIA402Axis->Axis_SetGearRatio(m_dGearingRatio);
    }
    if(AEC_SUCCESSED != res)
    {
        m_bError = true;
    }

    m_bDone = true;
    return;
}
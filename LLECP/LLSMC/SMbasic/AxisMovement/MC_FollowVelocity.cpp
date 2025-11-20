#include"MC_FollowVelocity.h"
MC_FollowVelocity::MC_FollowVelocity(/* args */)
{
}

MC_FollowVelocity::~MC_FollowVelocity()
{
}

void MC_FollowVelocity::operator()(CIA402Axis* axis)
{
    if(nullptr == axis)
    {
        return;
    }
    m_pCIA402Axis = axis;
}
void MC_FollowVelocity::operator()(CIA402Axis* axis,bool bExecute,double dVelocity,bool& bBusy,bool& bError,int& ErrorID)
{
    if(nullptr == axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    m_pCIA402Axis = axis;
    m_bExecute = bExecute;
    m_dVelocity = dVelocity;
    this->Execute();
    bBusy = m_bBusy;
    bError = m_bError;
    ErrorID = m_nErrorID;
}


void MC_FollowVelocity::Execute()
{
    if(nullptr == m_pCIA402Axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    //输出初始化
    m_bBusy             = false;
    m_bError            = false;
    m_nErrorID           = SMEC_SUCCESSED;
    int res = AEC_SUCCESSED;
    if(m_bExecute)
    {
        if(EN_ModesOfOperation::enModeCyclicSyncVelocity== m_pCIA402Axis->nActModeOpration)
            m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_synchronized_motion);
        res = m_pCIA402Axis->Axis_SetTargetVelocity(m_dVelocity);
    }
    if(AEC_SUCCESSED != res)
    {
        m_bError = true;
    }

    m_bBusy = true;
    return;
}
#include"MC_MoveVelocity.h"
MC_MoveVelocity::MC_MoveVelocity(/* args */)
{
}

MC_MoveVelocity::~MC_MoveVelocity()
{
}

void MC_MoveVelocity::operator()(CIA402Axis* axis)
{
    this->Execute();
}
void MC_MoveVelocity::operator()(CIA402Axis* axis,bool bExecute,double dVelocity,double dAcceleration,double dDeceleration,double dJerk,EN_Direction enDirection,
                    bool& bInVelocity,bool& bBusy,bool& bCommandAborted,bool& bError,int& ErrorID)
{
    m_pCIA402Axis                                   = axis;
    m_bExecute                                      = bExecute;
    m_MotionUint_New.PlanningMotionParam.vel            = abs(dVelocity) * enDirection;//方向校正
    m_MotionUint_New.PlanningMotionParam.acc            = abs(dAcceleration);
    m_MotionUint_New.PlanningMotionParam.dec            = abs(dDeceleration);
    m_MotionUint_New.PlanningMotionParam.jerk           = abs(dJerk);
    m_MotionUint_New.PlanningMotionParam.Direction      = enDirection;
    m_MotionUint_New.PlanningMotionParam.PlanningMode   = enVelocityPlanningMode;
    m_MotionUint_New.MoveType                           = enMoveTypeNull;
    m_MotionUint_New.fbID                               = this;
    m_MotionUint_New.fCallback                          = m_fCallback;
    //方向初始化
    m_MotionUint_New.PlanningMotionParam.vel = abs(m_MotionUint_New.PlanningMotionParam.vel)*m_MotionUint_New.PlanningMotionParam.Direction;
    this->Execute();
    bInVelocity = m_bInVelocity;
    bBusy = m_bBusy;
    bCommandAborted = m_bCommandAborted;
    bError = m_bError;
    ErrorID = m_nErrorID;
}

void MC_MoveVelocity::Execute()
{
    if(nullptr == m_pCIA402Axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    // 输出参数默认初始化
    m_bDone             = false;
    m_bBusy             = false;
    m_bCommandAborted   = false;
    m_bError            = false;
    m_nErrorID           = 0;
    
    //状态校验
    if(EN_AxisMotionState::motionState_errorstop == m_pCIA402Axis->Axis_ReadAxisState())
    {
        m_bError            = true;
        m_pCIA402Axis->Axis_CheckError(m_nErrorID);
        return;
    }
    if(m_bExecute)
    {
        if((EN_AxisMotionState::motionState_standstill != m_pCIA402Axis->Axis_ReadAxisState()) &&
             (EN_AxisMotionState::motionState_continuous_motion!= m_pCIA402Axis->Axis_ReadAxisState()) &&
                (EN_AxisMotionState::motionState_discrete_motion!= m_pCIA402Axis->Axis_ReadAxisState()))
        {
            m_nErrorID = SMEC_AXIS_STATUS_INTERCEPTION;
            m_bError = true;
        }
    }
    else
    {
        // 输出参数默认初始化
        m_bDone             = false;
        m_bBusy             = false;
        m_bCommandAborted   = false;
        m_bError            = false;
        m_nErrorID           = 0;
        return;
    }
    //上升沿push
    if(m_Timer.R_TRIG(m_bExecute))
    {
        m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_continuous_motion);
        m_MotionUint = m_MotionUint_New;
        m_pCIA402Axis->Axis_PushMotionUint(m_MotionUint);
    }
    //参数变更push
    if(m_MotionUint.PlanningMotionParam!=m_MotionUint_New.PlanningMotionParam)
    {
        m_MotionUint = m_MotionUint_New;
        m_pCIA402Axis->Axis_PushMotionUint(m_MotionUint);
    }
    ST_MotionUint FirstMotionUint;
    int nMotionNum = m_pCIA402Axis->Axis_GetMotionUint(FirstMotionUint);
    //点位小于0直接return
    if(nMotionNum < 0)
    {
        m_bCommandAborted = true;
        return;
    }
    //第一个点就是这个点
    if(this == FirstMotionUint.fbID)
    {
        //运动完成监测（速度运动理论上不会有完成标志）
        // if(FirstMotionUint.bMotionDone)
        // {
        //     m_bDone             = true;
        // }
        // else
        // {
        //     m_bBusy             = true;
        // }
        m_bBusy             = true;
    }
    //move被插其他块
    else
    {
        m_bCommandAborted = true;
        return;
    }
    return;
}
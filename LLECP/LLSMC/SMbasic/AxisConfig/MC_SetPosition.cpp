#include"MC_SetPosition.h"
MC_SetPosition::MC_SetPosition(/* args */)
{
}

MC_SetPosition::~MC_SetPosition()
{
}

void MC_SetPosition::operator()(CIA402Axis* axis)
{
    this->Execute();
}
void MC_SetPosition::operator()(CIA402Axis* axis,bool bExecute,double dPosition,bool &bDone, bool &bError,int &nErrorID)
{
    if((bExecute && m_bExecute)&&(axis != m_pCIA402Axis))
    {
        m_pCIA402Axis->Axis_SetAxisState(EN_AxisMotionState::motionState_errorstop);
        m_bBusy = false;
        m_bError = true;
        m_bDone = false;
        m_nErrorID = SMEC_ABNORMAL_AXIS_CHANGE;
    }
    m_pCIA402Axis = axis;
    m_bExecute = bExecute;
    this->Execute();
    m_bBusy = m_bBusy;
    bDone = m_bDone;
    bError = m_bError;
    nErrorID = m_nErrorID;
}


void MC_SetPosition::Execute()
{
    if(nullptr == m_pCIA402Axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
}
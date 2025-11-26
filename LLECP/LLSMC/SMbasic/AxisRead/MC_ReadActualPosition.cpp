#include"MC_ReadActualPosition.h"
MC_ReadActualPosition::MC_ReadActualPosition(/* args */)
{
}

MC_ReadActualPosition::~MC_ReadActualPosition()
{
}

void MC_ReadActualPosition::operator()(CIA402Axis* axis)
{
    if(nullptr == axis)
    {
        return;
    }
    m_pCIA402Axis = axis;
}
void MC_ReadActualPosition::operator()(CIA402Axis* axis,bool bExecute,bool& bValid,bool& bBusy,bool& bError,int& ErrorID,double& dPosition)
{
    if(nullptr == axis)
    {
        m_bError = true;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    m_pCIA402Axis = axis;
    m_bExecute = bExecute;
    this->Execute();
    bValid = m_bValid;
    dPosition = m_dPosition;
    bBusy = m_bBusy;
    bError = m_bError;
    ErrorID = m_nErrorID;
}


void MC_ReadActualPosition::Execute()
{
    if(nullptr == m_pCIA402Axis)
    {
        m_bError = true;
        m_bValid = false;
        m_nErrorID = SMEC_INVALID_AXIS;
        return;
    }
    //输出初始化
    m_bValid            = true;
    m_bBusy             = false;
    m_bError            = false;
    m_nErrorID          = SMEC_SUCCESSED;
    if(m_bExecute)
    {
        m_dPosition = m_pCIA402Axis->dActPosition;
    }
    m_bBusy = true;
    return;
}
#include"SMbasic.h"


SMbasic::SMbasic(/* args */)
{
    m_fCallback = [this](bool bBusy,bool bDone,bool bCommandAborted,bool bError,int nErrorID){this->SetFBStatus(bBusy,bDone,bCommandAborted,bError,nErrorID);};
}

SMbasic::~SMbasic()
{
}

void SMbasic::Execute()
{
    return;
}

void SMbasic::operator()(CIA402Axis* axis)
{
    m_pCIA402Axis = axis;
    Execute();
}

CIA402Axis  SMbasic::Axis()
{
    return m_pCIA402Axis;
}
bool SMbasic::Busy()
{
    Execute();
    return m_bBusy;
}
bool SMbasic::Done()
{
    Execute();
    return m_bDone;
}
bool SMbasic::Error()
{
    Execute();
    return m_bError;
}
bool SMbasic::ErrorID()
{
    Execute();
    return m_nErrorID;
}
int SMbasic::SetFBStatus(bool bBusy,bool bDone,bool bCommandAborted,bool bError,int nErrorID)
{
    m_bBusy = bBusy;
    m_bDone = bDone;
    m_bCommandAborted = bCommandAborted;
    m_bError = bError;
    m_nErrorID = nErrorID;
}
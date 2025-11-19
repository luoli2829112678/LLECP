#include"SMbasic.h"


SMbasic::SMbasic(/* args */)
{
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
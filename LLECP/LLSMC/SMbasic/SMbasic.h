#ifndef SMbasic_H
#define SMbasic_H
#include"../SoftMotion/SoftMotion.h"
#include"SMbasicErrorCode.h"
#include"SMbasicDef.h"
class SMbasic
{
protected:
    CIA402Axis* m_pCIA402Axis = nullptr;
    SMCTimer m_Timer;
    SMCTimer m_TimerTimeout;

    //Move类
    bool m_bExecute;
    double m_dPosition;
    double m_dVelocity;
    double m_dAcceleration;
    double m_dDeceleration;
    double m_dJerk;
    EN_Direction m_enDirection;
    EN_BufferMode m_enBufferMode;
    ST_MotionUint m_MotionUint;
    ST_MotionUint m_MotionUint_New;

    //通用
    bool m_bBusy;
    bool m_bCommandAborted;
    bool m_bDone;
    bool m_bError;
    int m_nErrorID;
public:
    SMbasic(/* args */);
    ~SMbasic();
    void operator()(CIA402Axis* axis);
    CIA402Axis Axis();
    bool Busy();
    bool Done();
    bool Error();
    bool ErrorID();
protected:
    virtual void Execute();
};
#endif // SMbasic_H
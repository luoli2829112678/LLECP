#include"../SMbasic.h"
class MC_PowerOn :public SMbasic
{
private:
    FS_PowerOn m_fsPowerOn;
    void Execute()override;

public:
    MC_PowerOn(/* args */);
    ~MC_PowerOn();

    void operator()(CIA402Axis* axis);
    void operator()(CIA402Axis* axis,bool bExecute,bool &bBusy,bool &bDone, bool &bError,int &nErrorID);
};

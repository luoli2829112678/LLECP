
#include"../SMbasic.h"
class MC_SetGearingRatio:public SMbasic
{
private:
    double m_dGearingRatio;
    void Execute()override;
public:
    MC_SetGearingRatio(/* args */);
    ~MC_SetGearingRatio();

    void operator()(CIA402Axis* axis);
    void operator()(CIA402Axis* axis,bool bExecute,double dGearingRatio,bool& bDone,bool& bError,int& ErrorID);
};


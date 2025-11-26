#include"../SMbasic.h"
class MC_ReadActualPosition:public SMbasic
{
private:
    double m_dPosition;
    bool m_bValid;
    void Execute()override;
public:
    MC_ReadActualPosition(/* args */);
    ~MC_ReadActualPosition();

    void operator()(CIA402Axis* axis);
    void operator()(CIA402Axis* axis,bool bExecute,bool& bValid,bool& bBusy,bool& bError,int& ErrorID,double& dPosition);
};

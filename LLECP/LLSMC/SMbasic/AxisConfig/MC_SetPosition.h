#include"../SMbasic.h"
class MC_SetPosition:public SMbasic
{
private:
    void Execute()override;
    /* data */
public:
    MC_SetPosition(/* args */);
    ~MC_SetPosition();
    void operator()(CIA402Axis* axis);
    void operator()(CIA402Axis* axis,bool bExecute,double dPosition,bool &bDone, bool &bError,int &nErrorID);
};


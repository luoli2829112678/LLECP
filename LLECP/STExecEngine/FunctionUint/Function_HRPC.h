#pragma once
#include"FunctionInfo.h"
class Function_HRPC: public FunctionInfo
{
private:
    int Execution()override;
    /* data */
public:
    Function_HRPC(/* args */);
    ~Function_HRPC();
};


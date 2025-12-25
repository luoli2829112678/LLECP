#pragma once
#include"../FunctionInfo.h"
class Function_AXIS_ENABLE: public FunctionInfo
{
protected:
    VariableUint Execution()override;
    /* data */
public:
    Function_AXIS_ENABLE(/* args */);
    ~Function_AXIS_ENABLE();
};

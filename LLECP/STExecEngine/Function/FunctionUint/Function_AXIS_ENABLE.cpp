#include "Function_AXIS_ENABLE.h"
Function_AXIS_ENABLE::Function_AXIS_ENABLE(/* args */)
{
    m_sFunctionName = "AXIS_ENABLE";
    m_bChechkInput = false;
}

Function_AXIS_ENABLE::~Function_AXIS_ENABLE()
{
}

VariableUint Function_AXIS_ENABLE::Execution()
{
    for (size_t i = 0; i < m_vInput.size(); i++)
    {
        BaseToken token = VariableUint2BaseToken(m_vInput[i]);
        int nAxis = static_cast<int>(token.KeywordAddr);
        printf("ENABLE Axis:%d\n", nAxis);
    }
    VariableUint res;
    
    return res;
}
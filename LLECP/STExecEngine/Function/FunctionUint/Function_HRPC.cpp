#include "Function_HRPC.h"
Function_HRPC::Function_HRPC(/* args */)
{
    m_sFunctionName = "HRPC";
    mmFunctionInput.insert(make_pair("p1",STRUCT_INFO_DINT));
    mmFunctionInput.insert(make_pair("p2",STRUCT_INFO_LREAL));
}

Function_HRPC::~Function_HRPC()
{
}

VariableUint Function_HRPC::Execution()
{

    VariableUint res;
    printf("HRPC EXECUTION\n");
    return res;
}
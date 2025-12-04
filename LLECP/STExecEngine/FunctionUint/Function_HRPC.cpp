#include "Function_HRPC.h"
Function_HRPC::Function_HRPC(/* args */)
{
    m_sFunctionName = "HRPC";
    mmFunctionInput.insert(make_pair("p1",STRUCT_INFO_INT));
    mmFunctionInput.insert(make_pair("p2",STRUCT_INFO_INT));

}

Function_HRPC::~Function_HRPC()
{
}

int Function_HRPC::Execution()
{
    Result.nStructInfoID = STRUCT_INFO_INT;
    Result.nVariableSize = 4;
    Result.pDataAddr = malloc(4);
    *(int32_t*)Result.pDataAddr = 42; // 示例返回值
    return 0;
}
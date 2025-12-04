#include"FunctionManager.h"

FunctionManager::FunctionManager(/* args */)
{
    Function_HRPC functionHRPC;
    m_vFunctionInfo.push_back(functionHRPC);
}

FunctionManager::~FunctionManager()
{
}

int FunctionManager::GetFunctionAddr(string sCmd)
{
    for (size_t i = 0; i < m_vFunctionInfo.size(); i++)
    {
        string FunctionName;
        m_vFunctionInfo[i].GetFunctionName(FunctionName);
        if(sCmd == FunctionName)
        {
            return i;
        }
    }
    
    printf("GetFunctionAddrERROR\n");
    return -1;
}

int FunctionManager::AddFunctionInfo(FunctionInfo functionInfo)
{
    m_vFunctionInfo.push_back(functionInfo);
    return 0;
}
FunctionInfo FunctionManager::GetFunction(int nAddr)
{
    return m_vFunctionInfo[nAddr];
}
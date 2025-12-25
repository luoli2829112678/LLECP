#include"FunctionManager.h"

FunctionManager::FunctionManager(/* args */)
{
    m_vFunctionInfo.push_back(std::make_unique<Function_HRPC>());
    m_vFunctionInfo.push_back(std::make_unique<Function_AXIS_ENABLE>());
}

FunctionManager::~FunctionManager()
{
}

int FunctionManager::GetFunctionAddr(const std::string& sCmd)
{
    for (size_t i = 0; i < m_vFunctionInfo.size(); i++)
    {
        std::string FunctionName;
        m_vFunctionInfo[i]->GetFunctionName(FunctionName);
        if (sCmd == FunctionName) return (int)i;
    }
    printf("GetFunctionAddrERROR\n");
    return -1;
}

int FunctionManager::AddFunctionInfo(std::unique_ptr<FunctionInfo> functionInfo)
{
    m_vFunctionInfo.push_back(std::move(functionInfo));
    return 0;
}

FunctionInfo* FunctionManager::GetFunction(int nAddr)
{
    return m_vFunctionInfo[nAddr].get();
}
#pragma once
#include<string>
#include <memory>
#include"../Function/FunctionInclude.h"
using namespace std;
class FunctionManager
{
private:
    std::vector<std::unique_ptr<FunctionInfo>> m_vFunctionInfo;
public:
    int GetFunctionAddr(const std::string& sCmd);
    int AddFunctionInfo(std::unique_ptr<FunctionInfo> functionInfo);
    FunctionInfo* GetFunction(int nAddr);
    FunctionManager(/* args */);
    ~FunctionManager();
};

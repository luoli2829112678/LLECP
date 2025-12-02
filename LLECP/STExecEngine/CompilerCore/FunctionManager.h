#pragma once
#include<string>
#include"../FunctionUint/FunctionInfo.h"
using namespace std;
class FunctionManager
{
private:
    vector<FunctionInfo>m_vFunctionInfo;
public:
    int GetFunctionAddr(string sCmd);
    int AddFunctionInfo(FunctionInfo functionInfo);
    FunctionManager(/* args */);
    ~FunctionManager();
};

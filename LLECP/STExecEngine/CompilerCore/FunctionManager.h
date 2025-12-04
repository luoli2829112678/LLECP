#pragma once
#include<string>
#include"../FunctionUint/FunctionInclude.h"
using namespace std;
class FunctionManager
{
private:
    vector<FunctionInfo>m_vFunctionInfo;
public:
    int GetFunctionAddr(string sCmd);
    int AddFunctionInfo(FunctionInfo functionInfo);
    FunctionInfo GetFunction(int nAddr);
    FunctionManager(/* args */);
    ~FunctionManager();
};

#pragma once
#include<string>
#include<vector>
#include"../CodeComponent/LineUint.h"
#include<map>
using namespace std;


class FunctionInfo
{
protected:
    string m_sFunctionName;
    map<string, int> mmFunctionInput;
    VariableUint Result;
    int virtual Execution();
public:
    FunctionInfo();
    VariableUint CallFunc(vector<VariableUint>Input);
    int GetFunctionName(string& sFunctionName);

    ~FunctionInfo();
};


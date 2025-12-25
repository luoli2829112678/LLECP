#pragma once
#include<string>
#include<vector>
#include"../CodeComponent/LineUint.h"
#include"../CompilerCore/VariableManager.h"

#include<map>
using namespace std;


class FunctionInfo
{
protected:
    string m_sFunctionName;
    bool m_bChechkInput;
    map<string, int> mmFunctionInput;//string和类型ID
    vector<VariableUint>m_vInput;
    VariableUint Result;
    virtual VariableUint Execution();   
public:
    FunctionInfo();
    VariableUint CallFunc(vector<VariableUint>Input);
    int GetFunctionName(string& sFunctionName);

    ~FunctionInfo();
};


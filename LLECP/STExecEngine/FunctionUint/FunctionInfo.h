#pragma once
#include<string>
#include<vector>
#include"../CodeComponent/LineUint.h"
#include<map>
using namespace std;


class FunctionInfo
{
private:
    string m_sFunctionName;
    map<string, int> mmFunctionInput;
    map<string, int> mmFunctionOutput;
    LineUint m_FunctionBody;
public:
    FunctionInfo( string sFunctionName,
                  map<string, int> mFunctionInput,
                  map<string, int> mFunctionOutput
                  );
    int InitFunctionBody(LineUint functionBody);
    int GetFunctionName(string& sFunctionName);
    ~FunctionInfo();
};


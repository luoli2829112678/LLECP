#include "FunctionInfo.h"

FunctionInfo::FunctionInfo( string sFunctionName,
                              map<string, int> mFunctionInput,
                              map<string, int> mFunctionOutput)
    :m_sFunctionName(sFunctionName),
     mmFunctionInput(mFunctionInput),
     mmFunctionOutput(mFunctionOutput)
{
    
}

FunctionInfo::~FunctionInfo()
{
}

int FunctionInfo::InitFunctionBody(LineUint functionBody)
{
     m_FunctionBody = functionBody;
     return 0;
}
int FunctionInfo::GetFunctionName(string& sFunctionName)
{
     sFunctionName = m_sFunctionName;
     return 0;
}
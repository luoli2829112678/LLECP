#include "FunctionInfo.h"

FunctionInfo::FunctionInfo()
{
    
}

FunctionInfo::~FunctionInfo()
{
}


int FunctionInfo::GetFunctionName(string& sFunctionName)
{
     sFunctionName = m_sFunctionName;
     return 0;
}
int FunctionInfo::Execution()
{
     return 0;
}
VariableUint FunctionInfo::CallFunc(vector<VariableUint>Input)
{
     if(mmFunctionInput.size() != Input.size())
     {
          printf("FunctionInfo::CallFunc input output size not match\n");
         return Result;
     }
     for (size_t i = 0; i < mmFunctionInput.size(); i++)
     {
          if(Input[i].nStructInfoID != std::next(mmFunctionInput.begin(),i)->second)
          {
               printf("FunctionInfo::CallFunc input name not match\n");
               return Result;
          }
     }
     //执行函数体 
     Execution();    
     return Result;
}
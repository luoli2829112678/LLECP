#include "FunctionInfo.h"

FunctionInfo::FunctionInfo()
{
    m_bChechkInput = true;
}

FunctionInfo::~FunctionInfo()
{
}


int FunctionInfo::GetFunctionName(string& sFunctionName)
{
     sFunctionName = m_sFunctionName;
     return 0;
}
VariableUint FunctionInfo::Execution()
{
     VariableUint res;
     return res;
}
VariableUint FunctionInfo::CallFunc(vector<VariableUint>Input)
{
     m_vInput = Input;
     if(!m_bChechkInput)
     {
          //不检查输入，直接执行
          return Execution();
     }
     //检查输入参数
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
     return Execution();    
}
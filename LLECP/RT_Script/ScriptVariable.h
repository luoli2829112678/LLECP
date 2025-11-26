#pragma once
#include<string>
#include <stdexcept>
#include"ScriptDefine.h"
class ScriptVariable
{
private:
    ScriptValue m_Data;
public:
    EN_VariableType m_VariableType;
    ScriptVariable(EN_VariableType Type);

    template<typename T>
    void SetVariable(const T& value);


    double GetVariable_Double();
    int GetVariable_INT32();
    uint32_t GetVariable_UINT32();
    bool GetVariable_BOOL();

    ~ScriptVariable();
};

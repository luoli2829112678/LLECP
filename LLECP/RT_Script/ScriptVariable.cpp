#include"ScriptVariable.h"
ScriptVariable::ScriptVariable(EN_VariableType Type)
{
    m_VariableType = Type;
}

ScriptVariable::~ScriptVariable()
{

}

double ScriptVariable::GetVariable_Double()
{
    return m_Data.baseValue.dData;
}

int ScriptVariable::GetVariable_INT32()
{
    return m_Data.baseValue.nData;
}

uint32_t ScriptVariable::GetVariable_UINT32()
{
    return m_Data.baseValue.unData;
}

bool ScriptVariable::GetVariable_BOOL()
{
    return m_Data.baseValue.bData;
}


template<>
void ScriptVariable::SetVariable<double>(const double& value) {
    m_Data.baseValue.dData = value;
}

template<>
void ScriptVariable::SetVariable<int>(const int& value) {
    m_Data.baseValue.nData = value;
}

template<>
void ScriptVariable::SetVariable<uint32_t>(const uint32_t& value) {
    m_Data.baseValue.unData = value;
}

template<>
void ScriptVariable::SetVariable<bool>(const bool& value) {
    m_Data.baseValue.bData = value;
}

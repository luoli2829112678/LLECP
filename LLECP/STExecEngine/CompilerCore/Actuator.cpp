#include"Actuator.h"

Actuator::Actuator(VariableManager* pVariableManager,StructManager* pStructManager,FunctionManager* pFunctionManager)
{
    m_pFunctionManager = pFunctionManager;
    m_pStructManager = pStructManager;
    m_pVariableManager = pVariableManager;
}

Actuator::~Actuator()
{
}

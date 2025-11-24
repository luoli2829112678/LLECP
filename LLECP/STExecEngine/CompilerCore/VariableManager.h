#pragma once
#include"../VariableUint/VariableUint.h"
#include <unordered_map>
class VariableManager
{
private:
    //var hash map
    std::unordered_map<std::string, VariableUint> m_GlobalVariable;
    std::unordered_map<std::string, VariableUint> m_BufferVariable[64];
public:
    int AddVariable(int buffID, const VariableUint& variable);
    VariableUint* FindVariable(int buffID, const std::string& name);
    VariableManager(/* args */);
    ~VariableManager();
};

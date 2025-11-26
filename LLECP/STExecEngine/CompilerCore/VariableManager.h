#pragma once
#include"../VariableUint/VariableUint.h"
#include <unordered_map>
class VariableManager
{
private:
    int m_nPushbuffID;
    StructManager* m_pStructManager;
    //var hash map
    std::unordered_map<std::string, VariableUint> m_GlobalVariable;
    std::unordered_map<std::string, VariableUint> m_BufferVariable[64];
public:
    int SetPushBufferID(int ID);
    int AddVariable(int buffID, const VariableUint& variable);
    VariableUint* FindVariable(int buffID, const std::string& name);
    int GetVariableAddr(string str);
    
    int GetVariableType(string str);

    VariableManager(StructManager* m_pStructManager);
    ~VariableManager();
};

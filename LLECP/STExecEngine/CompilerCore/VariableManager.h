#pragma once
#include"../VariableUint/VariableUint.h"
#include"./CodeComponent/BufferUint.h"
#include <unordered_map>
class VariableManager
{
private:
    int m_nPushbuffID;
    StructManager* m_pStructManager;
    //var hash map
    vector<VariableUint> m_GlobalVariable;
    vector<VariableUint> m_BufferVariable[64];
public:
    int SetPushBufferID(int ID);
    int AddVariable(int buffID, const VariableUint& variable);
    VariableUint* FindVariable(int buffID, const std::string& name);
    VariableUint* GetVariable(int buffID, int nAddr);
    int GetVariableAddr(string str);
    
    int GetVariableType(string str);

    VariableManager(StructManager* m_pStructManager);
    ~VariableManager();
};
BaseToken VariableUint2BaseToken(VariableUint var);
VariableUint BaseToken2VariableUint(BaseToken token);
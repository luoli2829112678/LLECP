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
    VariableUint* GetVariable(int buffID, string str);
    int GetVariableAddr(string str);
    
    int GetVariableType(string str);
    int SetVariable(int buffID, uint32_t addr,VariableUint variable);

    VariableManager(StructManager* m_pStructManager);
    ~VariableManager();
};
BaseToken VariableUint2BaseToken(VariableUint var);
VariableUint BaseToken2VariableUint(BaseToken token);
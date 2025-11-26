#include"VariableManager.h"
VariableManager::VariableManager(StructManager* pStructManager)
{
    m_pStructManager = pStructManager;
    VariableUint TestData = VariableUint(m_pStructManager,1,"HRPC");
    AddVariable(-1,TestData);
    for (size_t i = 0; i < 64; i++)
    {
        AddVariable(i,TestData);
    }
    m_pStructManager = pStructManager;
}

VariableManager::~VariableManager()
{
}
int VariableManager::SetPushBufferID(int ID)
{
    m_nPushbuffID = ID;
    return 0;
}
// buffID < 0  -> 全局变量表
// buffID >= 0 -> 对应的 Buffer 表（0~63）
int VariableManager::AddVariable(int buffID, const VariableUint& variable)
{
    // 变量名作为 key
    const std::string& name = variable.sVariableName;

    if (name.empty())
    {
        return -3; // 变量名为空，视为错误（可按需要调整）
    }

    if (buffID < 0)
    {
        // 全局变量
        auto result = m_GlobalVariable.emplace(name, variable); // 调用 VariableUint 的拷贝构造
        if (!result.second)
        {
            // 已经存在同名变量
            return -1;
        }
    }
    else
    {
        // Buffer 变量
        if (buffID >= 64)
        {
            return -2; // buffID 越界
        }

        auto& bufMap = m_BufferVariable[buffID];
        auto result = bufMap.emplace(name, variable); // 同样是拷贝构造
        if (!result.second)
        {
            // 已经存在同名变量
            return -1;
        }
    }

    return 0; // 成功
}

// 查找变量，找不到返回 nullptr
VariableUint* VariableManager::FindVariable(int buffID, const std::string& name)
{
    if (buffID < 0)
    {
        // 查全局变量
        auto it = m_GlobalVariable.find(name);
        if (it == m_GlobalVariable.end())
        {
            return nullptr;
        }
        return &it->second;
    }
    else
    {
        if (buffID >= 64)
        {
            return nullptr; // 越界，直接视为没找到
        }

        auto& bufMap = m_BufferVariable[buffID];
        auto it = bufMap.find(name);
        if (it == bufMap.end())
        {
            return nullptr;
        }
        return &it->second;
    }
}

int VariableManager::GetVariableAddr(string str)
{
    auto &bufMap = m_BufferVariable[m_nPushbuffID];

    int index = 0;
    //优先查找buffer变量
    for (auto it = bufMap.begin(); it != bufMap.end(); ++it, ++index)
    {
        if (it->first == str)
        {
            return index;   // 返回在这个 buffer 里的“第几个”
        }
    }
    //查找全局变量
    for (auto it = m_GlobalVariable.begin(); it != m_GlobalVariable.end(); ++it, ++index)
    {
        if (it->first == str)
        {
            return -index;   // 返回在这个 buffer 里的“第几个”
        }
    }
    printf("GetVariableAddrError\n");
    return 0;  // 没找到
}


int VariableManager::GetVariableType(string str)
{
    auto it = m_BufferVariable[m_nPushbuffID].find(str);
    if(nullptr == it)
    {
        printf("GetVariableTypeERROR\n");
        return -1;
    }
    return it->second.nStructInfoID;
}
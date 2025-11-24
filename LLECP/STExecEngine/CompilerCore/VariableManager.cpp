#include"VariableManager.h"
VariableManager::VariableManager(/* args */)
{
}

VariableManager::~VariableManager()
{
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
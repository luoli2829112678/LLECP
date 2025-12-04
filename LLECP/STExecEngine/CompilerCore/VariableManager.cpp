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
        for (size_t i = 0; i < m_GlobalVariable.size(); i++)
        {
            if(m_GlobalVariable[i].sVariableName == variable.sVariableName)
                // 已经存在同名变量
                return -1;
        }
        
        m_GlobalVariable.push_back( variable); // 调用 VariableUint 的拷贝构造
    }
    else
    {
        // Buffer 变量
        if (buffID >= 64)
        {
            return -2; // buffID 越界
        }
        for (size_t i = 0; i < m_BufferVariable[buffID].size(); i++)
        {
            if(m_BufferVariable[buffID][i].sVariableName == variable.sVariableName)
                // 已经存在同名变量
                return -1;
        }
        auto& bufMap = m_BufferVariable[buffID];
        bufMap.push_back(variable); // 同样是拷贝构造
    }

    return 0; // 成功
}

// 查找变量，找不到返回 nullptr
VariableUint* VariableManager::FindVariable(int buffID, const std::string& name)
{
    if (buffID < 0)
    {
        // 查全局变量
        for (size_t i = 0; i < m_GlobalVariable.size(); i++)
        {
            if(m_GlobalVariable[i].sVariableName == name)
                return &m_GlobalVariable[i];
        }
        return &m_GlobalVariable[0];
    }
    else
    {
        if (buffID >= 64)
        {
            return nullptr; // 越界，直接视为没找到
        }
        for (size_t i = 0; i < m_BufferVariable[buffID].size(); i++)
        {
            if(m_BufferVariable[buffID][i].sVariableName == name)
                return &m_BufferVariable[buffID][i];
        }
        return &m_GlobalVariable[0];
    }
}
VariableUint* VariableManager::GetVariable(int buffID, int nAddr)
{
    auto it = m_GlobalVariable.begin();
    if(buffID < 0)
    {
        buffID = 0 - buffID;
        for (size_t i = 0; i < buffID; i++)
        {
            it++;
        }
    }
    else
    {
        auto &bufMap = m_BufferVariable[buffID];
        it = bufMap.begin();
        for (size_t i = 0; i < nAddr; i++)
        {
            it++;
        }
    }
    return &(*it);
}

int VariableManager::GetVariableAddr(string str)
{
    auto &bufMap = m_BufferVariable[m_nPushbuffID];

    int index = 0;
    //优先查找buffer变量
    for (auto it = bufMap.begin(); it != bufMap.end(); ++it, ++index)
    {
        if (it->sVariableName == str)
        {
            return index;   // 返回在这个 buffer 里的“第几个”
        }
    }
    //查找全局变量
    for (auto it = m_GlobalVariable.begin(); it != m_GlobalVariable.end(); ++it, ++index)
    {
        if (it->sVariableName == str)
        {
            return -index;   // 返回在这个 buffer 里的“第几个”
        }
    }
    printf("GetVariableAddrError\n");
    return 0;  // 没找到
}


int VariableManager::GetVariableType(string str)
{
    for (size_t i = 0; i < m_BufferVariable[m_nPushbuffID].size(); i++)
    {
        if(m_BufferVariable[m_nPushbuffID][i].sVariableName == str)
            return m_BufferVariable[m_nPushbuffID][i].nStructInfoID;
    }
    printf("GetVariableTypeERROR\n");
    return -1;
}



BaseToken VariableUint2BaseToken(VariableUint var)
{
    BaseToken token;
    token.bInit = true;
    switch (var.nStructInfoID)
    {
    case STRUCT_INFO_NULL:
        token.enTokenType = TokenType_NULL;
        token.KeywordAddr = 0;
        break;
    case STRUCT_INFO_INT:
        token.enTokenType = TokenType_INTNumber;
        token.KeywordAddr = *(int16_t*)var.pDataAddr;
        break;
    case STRUCT_INFO_DINT:
        token.enTokenType = TokenType_INTNumber;    
        token.KeywordAddr = *(int32_t*)var.pDataAddr;
        break;
    case STRUCT_INFO_REAL:
        token.enTokenType = TokenType_DOUBLENumber;
        token.KeywordAddr = *(float*)var.pDataAddr;
        break;
    case STRUCT_INFO_LREAL:
        token.enTokenType = TokenType_DOUBLENumber;
        token.KeywordAddr = *(double*)var.pDataAddr;
        break;
    case STRUCT_INFO_BOOL:
        token.enTokenType = TokenType_INTNumber;
        token.KeywordAddr = (*(bool*)var.pDataAddr)?1:0;
        break;  
    case STRUCT_INFO_LONG:
        token.enTokenType = TokenType_INTNumber;
        token.KeywordAddr = *(long*)var.pDataAddr;
        break;  
    default:
        break;
    }
    return token;
}
VariableUint BaseToken2VariableUint(BaseToken token)
{
    VariableUint var;
    switch (token.enTokenType)
    {
    case TokenType_INTNumber:
        {
            int32_t val = static_cast<int32_t>(token.KeywordAddr);
            VariableUint var;
            var.nStructInfoID = STRUCT_INFO_DINT;
            var.nVariableSize = sizeof(int32_t);
            var.pDataAddr = new int32_t(val);
        }
        break;
    case TokenType_DOUBLENumber:
        {
            double val = token.KeywordAddr;
            VariableUint var;
            var.nStructInfoID = STRUCT_INFO_LREAL;
            var.nVariableSize = sizeof(double);
            var.pDataAddr = new double(val);
        }
        break;
    default:
        printf("BaseToken2VariableUintERROR:Unsupported variable type!\n");
        break;
    }
    return var;
}
#include"StructManager.h"
StructManager::StructManager(/* args */)
{
    InitStructManager();
}

StructManager::~StructManager()
{
    
}
int StructManager::AddStruct(string sName,vector<StructInfo>v_StructInfo)
{
    StructInfo t;
    t.sStructName = sName;
    t.sStructSize = 0;
    uint32_t offset = 0;
    for (size_t i = 0; i < v_StructInfo.size(); i++)
    {
        t.v_AddrOffset.push_back(offset);
        offset +=v_StructInfo[i].sStructSize;
        t.sStructSize += v_StructInfo[i].sStructSize;
        t.v_StructInfoIDList.push_back(v_StructInfo[i].StructInfoID);
    }
    t.StructInfoID = m_StructNum + 1;
    m_vStructInfo.push_back(t);
}
int StructManager::InitStructManager()
{
    StructInfo BOOL;
    BOOL.sStructName = "BOOL";
    BOOL.sStructSize = 1;
    BOOL.StructInfoID = 1;
    BOOL.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(BOOL);

    StructInfo INT;
    INT.sStructName = "INT";
    INT.sStructSize = 2;
    INT.StructInfoID = 2;
    INT.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(INT);

    StructInfo DINT;
    DINT.sStructName = "DINT";
    DINT.sStructSize = 4;
    DINT.StructInfoID = 3;
    DINT.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(DINT);

    StructInfo REAL;
    REAL.sStructName = "REAL";
    REAL.sStructSize = 4;
    REAL.StructInfoID = 4;
    REAL.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(REAL);

    StructInfo LREAL;
    LREAL.sStructName = "LREAL";
    LREAL.sStructSize = 8;
    LREAL.StructInfoID = 5;
    LREAL.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(LREAL);

    StructInfo LONG;
    LONG.sStructName = "LONG";
    LONG.sStructSize = 8;
    LONG.StructInfoID = 6;
    LONG.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(LONG);

    StructInfo STRING;
    STRING.sStructName = "STRING";
    STRING.sStructSize = STRINGSIZE;
    STRING.StructInfoID = 7;
    STRING.v_StructInfoIDList.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(STRING);
    


    return 0;
}


int StructManager::GetStructSize(int32_t nStructInfoID)
{
    for(size_t i = 0;i<m_vStructInfo.size();i++)
    {
        if(nStructInfoID == m_vStructInfo[i].StructInfoID)
        {
            return m_vStructInfo[i].sStructSize;
        }
    }
    return -1;
}
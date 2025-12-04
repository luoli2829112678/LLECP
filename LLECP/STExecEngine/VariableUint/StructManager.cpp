#include"StructManager.h"
StructManager::StructManager(/* args */)
{
    InitStructManager();
}

StructManager::~StructManager()
{
    
}
int StructManager::AddStruct(string sName,vector<StructInfo>v_StructInfo,vector<string>v_StructNameInfo)
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
        t.sStructName = v_StructNameInfo[i];
    }
    t.StructInfoID = m_StructNum + 1;
    m_vStructInfo.push_back(t);
    
    return 0;
}

int StructManager::GetVariableType(int nBaseType,string sName)
{
    for (size_t i = 0; i < m_vStructInfo[nBaseType].v_StructInfoNameList.size(); i++)
    {
        if(m_vStructInfo[nBaseType].v_StructInfoNameList[i] == sName)
            return m_vStructInfo[nBaseType].v_StructInfoIDList[i];
    }
    return -1;
}

int StructManager::GetVariableType(string sName)
{
    for (size_t i = 0; i < m_vStructInfo.size(); i++)
    {
        if(sName == m_vStructInfo[i].sStructName)
        {
            return m_vStructInfo[i].StructInfoID;
        }
    }
    printf("GetVariableTypeERROR\n");
    return -1;
}

int StructManager::InitStructManager()
{
    StructInfo null_;
    null_.sStructName = "NULL";
    null_.sStructSize = 0;
    null_.StructInfoID = 0;
    null_.v_StructInfoIDList.reserve(0);
    null_.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(null_);

    StructInfo BOOL;
    BOOL.sStructName = "BOOL";
    BOOL.sStructSize = 1;
    BOOL.StructInfoID = STRUCT_INFO_NULL;
    BOOL.v_StructInfoIDList.reserve(0);
    BOOL.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(BOOL);

    StructInfo INT;
    INT.sStructName = "INT";
    INT.sStructSize = 2;
    INT.StructInfoID = STRUCT_INFO_INT;
    INT.v_StructInfoIDList.reserve(0);
    INT.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(INT);

    StructInfo DINT;
    DINT.sStructName = "DINT";
    DINT.sStructSize = 4;
    DINT.StructInfoID = STRUCT_INFO_DINT;
    DINT.v_StructInfoIDList.reserve(0);
    DINT.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(DINT);

    StructInfo REAL;
    REAL.sStructName = "REAL";
    REAL.sStructSize = 4;
    REAL.StructInfoID = STRUCT_INFO_REAL;
    REAL.v_StructInfoIDList.reserve(0);
    REAL.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(REAL);

    StructInfo LREAL;
    LREAL.sStructName = "LREAL";
    LREAL.sStructSize = 8;
    LREAL.StructInfoID = STRUCT_INFO_LREAL;
    LREAL.v_StructInfoIDList.reserve(0);
    LREAL.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(LREAL);

    StructInfo LONG;
    LONG.sStructName = "LONG";
    LONG.sStructSize = 8;
    LONG.StructInfoID = STRUCT_INFO_LONG;
    LONG.v_StructInfoIDList.reserve(0);
    LONG.sStructName.reserve(0);
    m_StructNum ++;
    m_vStructInfo.push_back(LONG);

    StructInfo STRING;
    STRING.sStructName = STRUCT_INFO_STRING;
    STRING.sStructSize = STRINGSIZE;
    STRING.StructInfoID = 7;
    STRING.v_StructInfoIDList.reserve(0);
    STRING.sStructName.reserve(0);
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
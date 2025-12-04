#pragma once
#include"StructInfo.h"
#define STRINGSIZE 255
class StructManager
{
private:
    uint16_t m_StructNum ;
    vector<StructInfo>m_vStructInfo;
public:
    StructManager(/* args */);
    ~StructManager();
    int AddStruct(string sName,vector<StructInfo>v_StructInfo,vector<string>v_StructNameInfo);
    int GetStructSize(int32_t nStructInfoID);
    int GetVariableType(string sName);
    int GetVariableType(int nBaseType,string sName);
    int InitStructManager();
};

#define STRUCT_INFO_NULL 0
#define STRUCT_INFO_BOOL 1
#define STRUCT_INFO_INT 2
#define STRUCT_INFO_DINT 3 
#define STRUCT_INFO_REAL 4
#define STRUCT_INFO_LREAL 5
#define STRUCT_INFO_LONG 6 
#define STRUCT_INFO_STRING 7

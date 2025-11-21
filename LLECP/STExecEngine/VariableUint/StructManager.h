#include"StructInfo.h"
class StructManager
{
private:
    uint16_t m_StructNum ;
    vector<StructInfo>m_vStructInfo;
public:
    StructManager(/* args */);
    ~StructManager();
    int AddStruct(string sName,vector<StructInfo>v_StructInfo);
    int GetStructSize(int32_t nStructInfoID);
    int InitStructManager();
};


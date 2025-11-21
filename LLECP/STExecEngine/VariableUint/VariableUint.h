#include"StructManager.h"

class VariableUint
{
private:
    string sVariableName;
    uint32_t nVariableSize;
    uint32_t nStructInfoID;
    void* pDataAddr;
public:
    //构造函数传入数据类型以及变量名字
    VariableUint(StructManager* pStructManager, uint32_t nStructInfoID,string VariableName);
    ~VariableUint();
};


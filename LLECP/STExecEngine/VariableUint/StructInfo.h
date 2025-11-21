#include<string>
#include<vector>
using namespace std;


class StructInfo
{
public:
    string sStructName;
    uint32_t StructInfoID;
    //字节
    uint32_t sStructSize;
    //如果该类型为非基本类型，那么这个记录了各个子元素的偏移
    vector<uint32_t>v_AddrOffset;
    vector<uint32_t>v_StructInfoIDList;
public:
    StructInfo(/* args */);
    ~StructInfo();
};

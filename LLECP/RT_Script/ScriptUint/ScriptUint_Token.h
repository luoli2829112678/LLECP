
#include"Definition.h"
#include"CmdTypeDefine.h"


class ScriptUint_Token
{
public:
    friend class RT_ScriptSystem;
    EN_TokenType TokenType;
    //该变量用于记载Token为变量时为全局变量还是buff变量
    //-1为全局，正数为buff index -2为未初始化
    int16_t nRemarks;
    UN_TokenValue TokenValue;
public:
    ScriptUint_Token(/* args */);
    ~ScriptUint_Token();
};

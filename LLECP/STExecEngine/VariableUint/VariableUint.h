#pragma once
#include"StructManager.h"
#include <cstdlib>
#include <cstring>

class VariableUint
{
public:

    string sVariableName;
    int32_t nVariableSize;
    int32_t nStructInfoID;
    void* pDataAddr;
public:
    VariableUint() = default;

    // 带类型 + 名字构造
    VariableUint(StructManager* pStructManager,
                 uint32_t structInfoID,
                 const std::string& variableName);

    // 深拷贝
    VariableUint(const VariableUint& other);
    VariableUint& operator=(const VariableUint& other);

    // 禁止移动（防止“只搬指针”的语义混进来）
    VariableUint(VariableUint&& other);
    VariableUint& operator=(VariableUint&& other);

    ~VariableUint();
};
//加
int VariableUint_ADD(VariableUint* x,VariableUint* y,VariableUint &add);
//减
int VariableUint_SUB(VariableUint* x,VariableUint* y, VariableUint &sub);
//乘
int VariableUint_MUL(VariableUint* x,VariableUint* y, VariableUint &mul);
//除
int VariableUint_DIV(VariableUint* x,VariableUint* y, VariableUint &divv);
//与
int VariableUint_AND(VariableUint* x,VariableUint* y, VariableUint &res);
//或
int VariableUint_OR(VariableUint* x,VariableUint* y, VariableUint &res);
//非
int VariableUint_NOT(VariableUint* x, VariableUint &res);
//异或
int VariableUint_XOR(VariableUint* x,VariableUint* y, VariableUint &res);
//左移
int VariableUint_SHL(VariableUint* x, VariableUint* n, VariableUint &res);
//右移
int VariableUint_SHR(VariableUint* x, VariableUint* n, VariableUint &res);
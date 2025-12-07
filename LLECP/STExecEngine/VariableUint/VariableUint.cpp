#include"VariableUint.h"
VariableUint::VariableUint()
{
    sVariableName = "null";
    nVariableSize = 0;
    nStructInfoID = -1;
    pDataAddr     = nullptr;
}
// 普通构造：根据类型ID向 StructManager 要大小，然后 malloc
VariableUint::VariableUint(StructManager* pStructManager,
                           uint32_t structInfoID,
                           const std::string& variableName)
{
    nStructInfoID = structInfoID;
    sVariableName = variableName;
    nVariableSize = pStructManager ? pStructManager->GetStructSize(structInfoID) : 0;

    if (nVariableSize > 0)
    {
        pDataAddr = std::malloc(nVariableSize);
        if (pDataAddr)
        {
            std::memset(pDataAddr, 0, nVariableSize);  // 可选：初始化为0
        }
    }
    else
    {
        printf("VariableUinterror!\n");
        pDataAddr = nullptr;
    }
}

//  移动构造：偷指针 + 清空源
VariableUint::VariableUint(VariableUint&& other) 
{
    sVariableName = std::move(other.sVariableName);
    nVariableSize = other.nVariableSize;
    nStructInfoID = other.nStructInfoID;
    pDataAddr     = other.pDataAddr;

    // 把源对象清空，防止析构时二次释放
    other.nVariableSize = 0;
    other.nStructInfoID = -1;
    other.pDataAddr     = nullptr;
}

//  移动赋值：释放自己 → 偷指针 → 清空源
VariableUint& VariableUint::operator=(VariableUint&& other) 
{
    if (this != &other)
    {
        // 先释放自己原有资源
        if (pDataAddr)
        {
            std::free(pDataAddr);
            pDataAddr = nullptr;
        }

        sVariableName = std::move(other.sVariableName);
        nVariableSize = other.nVariableSize;
        nStructInfoID = other.nStructInfoID;
        pDataAddr     = other.pDataAddr;

        other.nVariableSize = 0;
        other.nStructInfoID = -1;
        other.pDataAddr     = nullptr;
    }
    return *this;
}

//  深拷贝构造
VariableUint::VariableUint(const VariableUint& other)
{
    sVariableName = other.sVariableName;
    nVariableSize = other.nVariableSize;
    nStructInfoID = other.nStructInfoID;

    if (other.pDataAddr && nVariableSize > 0)
    {
        pDataAddr = std::malloc(nVariableSize);
        if (pDataAddr)
        {
            std::memcpy(pDataAddr, other.pDataAddr, nVariableSize);
        }
    }
    else
    {
        pDataAddr = nullptr;
    }
}

//  深拷贝赋值
VariableUint& VariableUint::operator=(const VariableUint& other)
{
    if (this == &other)
        return *this;

    // 释放自己原来的内存
    if (pDataAddr)
    {
        std::free(pDataAddr);
        pDataAddr = nullptr;
    }

    sVariableName = other.sVariableName;
    nVariableSize = other.nVariableSize;
    nStructInfoID = other.nStructInfoID;

    if (other.pDataAddr && nVariableSize > 0)
    {
        pDataAddr = std::malloc(nVariableSize);
        if (pDataAddr)
        {
            std::memcpy(pDataAddr, other.pDataAddr, nVariableSize);
        }
    }
    else
    {
        pDataAddr = nullptr;
    }

    return *this;
}

VariableUint::~VariableUint()
{
    if (pDataAddr)
    {
        std::free(pDataAddr);
        pDataAddr = nullptr;
    }
}

int VariableUint_ADD(VariableUint* x,VariableUint* y,VariableUint &add)
{
    // 1. 类型必须一致
    if (x->nStructInfoID != y->nStructInfoID)
    {
        return -1;    // 类型不一致
    }

    // 2. 限制只对基础类型(1~8)做加法
    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
    {
        return -2;    // 不支持的类型
    }

    // 3. add 也必须同类型（防止传错容器）
    if (add.nStructInfoID != x->nStructInfoID)
    {
        return -3;    // 结果变量类型不匹配
    }

    // 4. 指针判空
    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || add.pDataAddr == nullptr)
    {
        return -4;    // 内存未初始化
    }
    switch (x->nStructInfoID)
    {
    case 1: // BOOL：这里随便给个定义，我用“逻辑或”当加法，也可以直接转成 int 相加
        {
            bool xv = *(bool*)x->pDataAddr;
            bool yv = *(bool*)y->pDataAddr;
            *(bool*)add.pDataAddr = (xv || yv);
        }
        break;

    case 2: // INT（16 位有符号）
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            *(int16_t*)add.pDataAddr = (int16_t)(xv + yv);
        }
        break;

    case 3: // DINT（32 位有符号）
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            *(int32_t*)add.pDataAddr = xv + yv;
        }
        break;

    case 4: // REAL（float）
        {
            float xv = *(float*)x->pDataAddr;
            float yv = *(float*)y->pDataAddr;
            *(float*)add.pDataAddr = xv + yv;
        }
        break;

    case 5: // LREAL（double）
        {
            double xv = *(double*)x->pDataAddr;
            double yv = *(double*)y->pDataAddr;
            *(double*)add.pDataAddr = xv + yv;
        }
        break;

    case 6: // LONG（这里我按 64 位有符号整数处理）
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            *(int64_t*)add.pDataAddr = xv + yv;
        }
        break;

    // 如果你后面给 7、8 也定义类型，在这里继续加分支即可
    default:
        return -5;  // 未实现的基础类型
    }

    return 0;   // 成功
}

int VariableUint_SUB(VariableUint* x,VariableUint* y, VariableUint &sub)
{
    // 1. 类型必须一致
    if (x->nStructInfoID != y->nStructInfoID)
        return -1;

    // 2. 限制只对基础类型(1~6)做运算
    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
        return -2;

    // 3. 结果类型必须一致
    if (sub.nStructInfoID != x->nStructInfoID)
        return -3;

    // 4. 指针判空
    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || sub.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 不支持减法
        return -5;

    case 2: // INT（16位）
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            *(int16_t*)sub.pDataAddr = (int16_t)(xv - yv);
        }
        break;

    case 3: // DINT（32位）
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            *(int32_t*)sub.pDataAddr = xv - yv;
        }
        break;

    case 4: // REAL（float）
        {
            float xv = *(float*)x->pDataAddr;
            float yv = *(float*)y->pDataAddr;
            *(float*)sub.pDataAddr = xv - yv;
        }
        break;

    case 5: // LREAL（double）
        {
            double xv = *(double*)x->pDataAddr;
            double yv = *(double*)y->pDataAddr;
            *(double*)sub.pDataAddr = xv - yv;
        }
        break;

    case 6: // LONG（64位整数）
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            *(int64_t*)sub.pDataAddr = xv - yv;
        }
        break;

    default:
        return -5;
    }

    return 0;
}

int VariableUint_MUL(VariableUint* x,VariableUint* y, VariableUint &mul)
{
    if (x->nStructInfoID != y->nStructInfoID)
        return -1;

    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
        return -2;

    if (mul.nStructInfoID != x->nStructInfoID)
        return -3;

    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || mul.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 不支持乘法
        return -5;

    case 2: // INT
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            *(int16_t*)mul.pDataAddr = (int16_t)(xv * yv);
        }
        break;

    case 3: // DINT
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            *(int32_t*)mul.pDataAddr = xv * yv;
        }
        break;

    case 4: // REAL
        {
            float xv = *(float*)x->pDataAddr;
            float yv = *(float*)y->pDataAddr;
            *(float*)mul.pDataAddr = xv * yv;
        }
        break;

    case 5: // LREAL
        {
            double xv = *(double*)x->pDataAddr;
            double yv = *(double*)y->pDataAddr;
            *(double*)mul.pDataAddr = xv * yv;
        }
        break;

    case 6: // LONG
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            *(int64_t*)mul.pDataAddr = xv * yv;
        }
        break;

    default:
        return -5;
    }

    return 0;
}

int VariableUint_DIV(VariableUint* x,VariableUint* y, VariableUint &divv)
{
    if (x->nStructInfoID != y->nStructInfoID)
        return -1;

    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
        return -2;

    if (divv.nStructInfoID != x->nStructInfoID)
        return -3;

    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || divv.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 不支持除法
        return -5;

    case 2: // INT
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            if (yv == 0) return -6;  // 除零
            *(int16_t*)divv.pDataAddr = (int16_t)(xv / yv);
        }
        break;

    case 3: // DINT
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            if (yv == 0) return -6;
            *(int32_t*)divv.pDataAddr = xv / yv;
        }
        break;

    case 4: // REAL
        {
            float xv = *(float*)x->pDataAddr;
            float yv = *(float*)y->pDataAddr;
            if (yv == 0.0f) return -6;
            *(float*)divv.pDataAddr = xv / yv;
        }
        break;

    case 5: // LREAL
        {
            double xv = *(double*)x->pDataAddr;
            double yv = *(double*)y->pDataAddr;
            if (yv == 0.0) return -6;
            *(double*)divv.pDataAddr = xv / yv;
        }
        break;

    case 6: // LONG
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            if (yv == 0) return -6;
            *(int64_t*)divv.pDataAddr = xv / yv;
        }
        break;

    default:
        return -5;
    }

    return 0;
}

int VariableUint_AND(VariableUint* x,VariableUint* y, VariableUint &res)
{
    if (x->nStructInfoID != y->nStructInfoID)
        return -1;

    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
        return -2;

    if (res.nStructInfoID != x->nStructInfoID)
        return -3;

    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || res.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 逻辑与
        {
            bool xv = *(bool*)x->pDataAddr;
            bool yv = *(bool*)y->pDataAddr;
            *(bool*)res.pDataAddr = (xv && yv);
        }
        break;

    case 2: // INT 按位与
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            *(int16_t*)res.pDataAddr = (int16_t)(xv & yv);
        }
        break;

    case 3: // DINT 按位与
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            *(int32_t*)res.pDataAddr = xv & yv;
        }
        break;

    case 6: // LONG 按位与
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            *(int64_t*)res.pDataAddr = xv & yv;
        }
        break;

    case 4: // REAL
    case 5: // LREAL
        // 浮点按位与一般没有意义，这里直接不支持
        return -5;

    default:
        return -5;
    }

    return 0;
}

int VariableUint_OR(VariableUint* x,VariableUint* y, VariableUint &res)
{
    if (x->nStructInfoID != y->nStructInfoID)
        return -1;

    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
        return -2;

    if (res.nStructInfoID != x->nStructInfoID)
        return -3;

    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || res.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 逻辑或
        {
            bool xv = *(bool*)x->pDataAddr;
            bool yv = *(bool*)y->pDataAddr;
            *(bool*)res.pDataAddr = (xv || yv);
        }
        break;

    case 2: // INT 按位或
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            *(int16_t*)res.pDataAddr = (int16_t)(xv | yv);
        }
        break;

    case 3: // DINT 按位或
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            *(int32_t*)res.pDataAddr = xv | yv;
        }
        break;

    case 6: // LONG 按位或
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            *(int64_t*)res.pDataAddr = xv | yv;
        }
        break;

    case 4: // REAL
    case 5: // LREAL
        return -5;

    default:
        return -5;
    }

    return 0;
}

int VariableUint_NOT(VariableUint* x, VariableUint &res)
{
    if (x->nStructInfoID != res.nStructInfoID)
        return -1;

    if (x->nStructInfoID > 6)
        return -2;

    if (x->pDataAddr == nullptr || res.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 逻辑非
        {
            bool xv = *(bool*)x->pDataAddr;
            *(bool*)res.pDataAddr = !xv;
        }
        break;

    case 2: // INT 按位取反
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            *(int16_t*)res.pDataAddr = (int16_t)(~xv);
        }
        break;

    case 3: // DINT 按位取反
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            *(int32_t*)res.pDataAddr = ~xv;
        }
        break;

    case 6: // LONG 按位取反
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            *(int64_t*)res.pDataAddr = ~xv;
        }
        break;

    case 4: // REAL
    case 5: // LREAL
        // 浮点没有按位NOT的通用语义，这里先不支持
        return -5;

    default:
        return -5;
    }

    return 0;
}

int VariableUint_XOR(VariableUint* x,VariableUint* y, VariableUint &res)
{
    // 1. 类型必须一致
    if (x->nStructInfoID != y->nStructInfoID)
        return -1;

    // 2. 限制只对基础类型(1~6)做运算
    if ((x->nStructInfoID > 6) || (y->nStructInfoID > 6))
        return -2;

    // 3. 结果类型必须一致
    if (res.nStructInfoID != x->nStructInfoID)
        return -3;

    // 4. 指针判空
    if (x->pDataAddr == nullptr || y->pDataAddr == nullptr || res.pDataAddr == nullptr)
        return -4;

    switch (x->nStructInfoID)
    {
    case 1: // BOOL 逻辑异或
        {
            bool xv = *(bool*)x->pDataAddr;
            bool yv = *(bool*)y->pDataAddr;
            *(bool*)res.pDataAddr = (xv != yv);
        }
        break;

    case 2: // INT 按位异或
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t yv = *(int16_t*)y->pDataAddr;
            *(int16_t*)res.pDataAddr = (int16_t)(xv ^ yv);
        }
        break;

    case 3: // DINT 按位异或
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t yv = *(int32_t*)y->pDataAddr;
            *(int32_t*)res.pDataAddr = xv ^ yv;
        }
        break;

    case 6: // LONG 按位异或（64 位）
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t yv = *(int64_t*)y->pDataAddr;
            *(int64_t*)res.pDataAddr = xv ^ yv;
        }
        break;

    case 4: // REAL
    case 5: // LREAL
        return -5;   // 不支持对浮点做位运算

    default:
        return -5;
    }

    return 0;
}

int VariableUint_SHL(VariableUint* x, VariableUint* n, VariableUint &res)
{
    // x 和 res 类型必须一致
    if (x->nStructInfoID != res.nStructInfoID)
        return -1;

    // 只支持 1~6
    if (x->nStructInfoID > 6 || n->nStructInfoID > 6)
        return -2;

    // 指针判空
    if (x->pDataAddr == nullptr || n->pDataAddr == nullptr || res.pDataAddr == nullptr)
        return -4;

    // 取移位次数（n 必须是整型）
    int32_t shift = 0;
    switch (n->nStructInfoID)
    {
    case 2: // INT
        shift = *(int16_t*)n->pDataAddr;
        break;
    case 3: // DINT
        shift = *(int32_t*)n->pDataAddr;
        break;
    case 6: // LONG
        {
            int64_t tmp = *(int64_t*)n->pDataAddr;
            shift = (int32_t)tmp;
        }
        break;
    default:
        return -3;  // 移位次数不是整数类型
    }

    if (shift < 0)
        return -6;  // 不允许负移位

    switch (x->nStructInfoID)
    {
    case 1: // BOOL：左移其实没太大意义，这里定义为：false<<n = false, true<<0 = true, 其它按 false
        {
            bool xv = *(bool*)x->pDataAddr;
            bool rv = (shift == 0) ? xv : false;
            *(bool*)res.pDataAddr = rv;
        }
        break;

    case 2: // INT
        {
            uint16_t xv = *(int16_t*)x->pDataAddr;
            uint16_t rv = (shift >= 16) ? 0 : (xv << shift);
            *(int16_t*)res.pDataAddr = (int16_t)rv;
        }
        break;

    case 3: // DINT
        {
            uint32_t xv = *(int32_t*)x->pDataAddr;
            uint32_t rv = (shift >= 32) ? 0 : (xv << shift);
            *(int32_t*)res.pDataAddr = (int32_t)rv;
        }
        break;

    case 6: // LONG
        {
            uint64_t xv = *(int64_t*)x->pDataAddr;
            uint64_t rv = (shift >= 64) ? 0 : (xv << shift);
            *(int64_t*)res.pDataAddr = (int64_t)rv;
        }
        break;

    case 4: // REAL
    case 5: // LREAL
        return -5;  // 不支持浮点
    default:
        return -5;
    }

    return 0;
}

int VariableUint_SHR(VariableUint* x, VariableUint* n, VariableUint &res)
{
    // x 和 res 类型必须一致
    if (x->nStructInfoID != res.nStructInfoID)
        return -1;

    if (x->nStructInfoID > 6 || n->nStructInfoID > 6)
        return -2;

    if (x->pDataAddr == nullptr || n->pDataAddr == nullptr || res.pDataAddr == nullptr)
        return -4;

    // 取移位次数
    int32_t shift = 0;
    switch (n->nStructInfoID)
    {
    case 2: // INT
        shift = *(int16_t*)n->pDataAddr;
        break;
    case 3: // DINT
        shift = *(int32_t*)n->pDataAddr;
        break;
    case 6: // LONG
        {
            int64_t tmp = *(int64_t*)n->pDataAddr;
            shift = (int32_t)tmp;
        }
        break;
    default:
        return -3; // 移位次数不是整数
    }

    if (shift < 0)
        return -6;  // 不允许负移位

    switch (x->nStructInfoID)
    {
    case 1: // BOOL：右移定义同左移
        {
            bool xv = *(bool*)x->pDataAddr;
            bool rv = (shift == 0) ? xv : false;
            *(bool*)res.pDataAddr = rv;
        }
        break;

    case 2: // INT：算术右移
        {
            int16_t xv = *(int16_t*)x->pDataAddr;
            int16_t rv;
            if (shift >= 15)
            {
                // 全部移掉，保留符号
                rv = (xv < 0) ? (int16_t)-1 : (int16_t)0;
            }
            else
            {
                rv = (int16_t)(xv >> shift);
            }
            *(int16_t*)res.pDataAddr = rv;
        }
        break;

    case 3: // DINT：算术右移
        {
            int32_t xv = *(int32_t*)x->pDataAddr;
            int32_t rv;
            if (shift >= 31)
            {
                rv = (xv < 0) ? -1 : 0;
            }
            else
            {
                rv = xv >> shift;
            }
            *(int32_t*)res.pDataAddr = rv;
        }
        break;

    case 6: // LONG：算术右移
        {
            int64_t xv = *(int64_t*)x->pDataAddr;
            int64_t rv;
            if (shift >= 63)
            {
                rv = (xv < 0) ? (int64_t)-1 : (int64_t)0;
            }
            else
            {
                rv = xv >> shift;
            }
            *(int64_t*)res.pDataAddr = rv;
        }
        break;

    case 4: // REAL
    case 5: // LREAL
        return -5;

    default:
        return -5;
    }

    return 0;
}


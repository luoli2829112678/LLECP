#pragma once
#include"UintDef.h"
#include<vector>
#include<string>
#include <stdint.h>
#include <chrono>
#include <iostream>
class BaseToken
{
public:
    EN_TokenType enTokenType;
    bool bInit;
    //如果是变量，那么这个值是变量地址、正数代表全局变量，负数为buff变量
    //如果是操作符、那么是枚举
    //如果是函数、那么是函数地址
    //如果是逻辑语句、那么是枚举
    //如果是数字，那么这个就是数字值，因此为64位
    //......
    double KeywordAddr;
    uint8_t nBuffID;
    //结构体偏移
    std::vector<int16_t>v_nSTOffset;
    //数组偏移
    std::vector<int16_t>v_nArrOffset;
public:
    BaseToken(/* args */);
    ~BaseToken();
};

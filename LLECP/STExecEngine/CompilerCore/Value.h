// Value.h
#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

struct Value {
    enum class Type { NONE, INT, REAL, BOOL } type = Type::NONE;

    long long i = 0;
    double    r = 0.0;
    bool      b = false;

    static Value makeInt(long long v) {
        Value val;
        val.type = Type::INT;
        val.i = v;
        val.r = static_cast<double>(v);
        return val;
    }

    static Value makeReal(double v) {
        Value val;
        val.type = Type::REAL;
        val.r = v;
        val.i = static_cast<long long>(v);
        return val;
    }

    static Value makeBool(bool v) {
        Value val;
        val.type = Type::BOOL;
        val.b = v;
        return val;
    }

    static Value makeNone() {
        return Value{};
    }

    // 数值型（INT/LREAL）转 double
    double toReal() const {
        switch (type) {
        case Type::INT:  return static_cast<double>(i);
        case Type::REAL: return r;
        default:
            throw std::runtime_error("不能把非数值类型转换为实数");
        }
    }

    // 逻辑运算使用
    bool toBool() const {
        switch (type) {
        case Type::BOOL: return b;
        case Type::INT:  return (i != 0);
        case Type::REAL: return (r != 0.0);
        default:
            return false;
        }
    }

    std::string toString() const {
        switch (type) {
        case Type::INT:  return std::to_string(i);
        case Type::REAL: return std::to_string(r);
        case Type::BOOL: return b ? "TRUE" : "FALSE";
        default:         return "<NONE>";
        }
    }
};

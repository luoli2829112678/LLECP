#include"RT_Script.h"
double RT_ScriptSystem::RT_ScriptCalculator(std::vector<ScriptUint_Token> v_Token)
{
    //执行器校验括号
    for(uint32_t i = 0;i<v_Token.size();i++)
    {
        uint8_t nFuntionCout = 0;
        //寻找括号
        if(v_Token[i].TokenType == TokenType_Delimiter)
        {
            //寻找尾括号
            if(v_Token[i-1].TokenType != TokenType_Function)
            {
                auto it = v_Token.end();
                for(uint32_t j = v_Token.size();j>0;j--)
                {
                    if(it->TokenType == TokenType_Delimiter)
                    {
                        if(0 == nFuntionCout)
                        {
                            std::vector<ScriptUint_Token> inner(v_Token.begin() + i + 1, v_Token.begin() + j);
                            ScriptUint_Token newToken;
                            newToken.TokenType = TokenType_Number;
                            newToken.TokenValue.NumberValue = RT_ScriptCalculator(inner);
                            //再删除期间的Token
                            v_Token.erase(v_Token.begin() + i, v_Token.begin() + j + 1);
                            //用新值的Token替换掉原来的括号一大堆Token
                            v_Token.insert(v_Token.begin() + i,newToken);
                            break;
                        }
                        else
                        {
                            nFuntionCout++;
                        }
                    }
                    it --;
                }
            }
            //是函数的括号
            else
            {
                nFuntionCout++;
            }
        }

    }
    //已经没有括号了变量全部转换成数字
    for(uint32_t i = 0;i<v_Token.size();i++)
    {
        //变量拿出数据来
        if(v_Token[i].TokenType == TokenType_Variable)
        {
            v_Token[i].TokenType = TokenType_Number;
            if(-1 == v_Token[i].nRemarks)
            {
                auto it = m_ScriptVariableGlobal.begin();
                std::advance(it, v_Token[i].TokenValue.KeywordAddr);
                v_Token[i].TokenValue.NumberValue = it->second.GetVariable_Double();
            }
            else
            {
                auto it = m_ScriptVariableBuffer[v_Token[i].nRemarks].begin();
                std::advance(it, v_Token[i].TokenValue.KeywordAddr);
                v_Token[i].TokenValue.NumberValue = it->second.GetVariable_Double();
            }
        }

    }
    //进行运算
    //首先是* / 符号
    for(uint32_t i = 0;i<v_Token.size();i++)
    {
        ScriptUint_Token tToken;
        tToken.TokenType = TokenType_Number;
        if((v_Token[i].TokenType == TokenType_Operator)&&(v_Token[i].TokenValue.OperatorType == OperatorType_Ride || v_Token[i].TokenValue.OperatorType == OperatorType_Division))
        {
            //乘法计算
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Ride)
            {
                tToken.TokenValue.NumberValue = v_Token[i-1].TokenValue.NumberValue * v_Token[i+1].TokenValue.NumberValue;
            }
            //除法计算
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Division)
            {
                tToken.TokenValue.NumberValue = v_Token[i-1].TokenValue.NumberValue / v_Token[i+1].TokenValue.NumberValue;
            }
            v_Token[i] = tToken;
            v_Token.erase(v_Token.begin()+i -1);
            v_Token.erase(v_Token.begin()+i +1);
        }
    }
    //第二是+ -
    for(uint32_t i = 0;i<v_Token.size();i++)
    {
        ScriptUint_Token tToken;
        tToken.TokenType = TokenType_Number;
        if((v_Token[i].TokenType == TokenType_Operator)&&(v_Token[i].TokenValue.OperatorType == OperatorType_PLUS || v_Token[i].TokenValue.OperatorType == OperatorType_Subtract))
        {
            //乘法计算
            if(v_Token[i].TokenValue.OperatorType == OperatorType_PLUS)
            {
                tToken.TokenValue.NumberValue = v_Token[i-1].TokenValue.NumberValue + v_Token[i+1].TokenValue.NumberValue;
            }
            //除法计算
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Subtract)
            {
                tToken.TokenValue.NumberValue = v_Token[i-1].TokenValue.NumberValue - v_Token[i+1].TokenValue.NumberValue;
            }
            v_Token[i] = tToken;
            v_Token.erase(v_Token.begin()+i -1);
            v_Token.erase(v_Token.begin()+i +1);
        }
    }
    //第三是< <= > >=
    for(uint32_t i = 0;i<v_Token.size();i++)
    {
        ScriptUint_Token tToken;
        tToken.TokenType = TokenType_Number;
        if((v_Token[i].TokenType == TokenType_Operator)&&(v_Token[i].TokenValue.OperatorType == OperatorType_Greater || v_Token[i].TokenValue.OperatorType == OperatorType_Less
                                                        || v_Token[i].TokenValue.OperatorType == OperatorType_GreaterEqual || v_Token[i].TokenValue.OperatorType == OperatorType_LessEqual))
        {
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Greater)
            {
                tToken.TokenValue.NumberValue = v_Token[i-1].TokenValue.NumberValue > v_Token[i+1].TokenValue.NumberValue;
            }
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Less)
            {
                tToken.TokenValue.NumberValue = v_Token[i-1].TokenValue.NumberValue < v_Token[i+1].TokenValue.NumberValue;
            }
            //double比较等于以0.000001为精度
            if(v_Token[i].TokenValue.OperatorType == OperatorType_GreaterEqual)
            {
                tToken.TokenValue.NumberValue = (v_Token[i-1].TokenValue.NumberValue - v_Token[i+1].TokenValue.NumberValue) > -0.000001;
            }
            if(v_Token[i].TokenValue.OperatorType == OperatorType_LessEqual)
            {
                tToken.TokenValue.NumberValue = (v_Token[i-1].TokenValue.NumberValue <= v_Token[i+1].TokenValue.NumberValue) < 0.000001;
            }
            v_Token[i] = tToken;
            v_Token.erase(v_Token.begin()+i -1);
            v_Token.erase(v_Token.begin()+i +1);
        }
    }
    //第四是 == !=
    for(uint32_t i = 0;i<v_Token.size();i++)
    {
        ScriptUint_Token tToken;
        tToken.TokenType = TokenType_Number;
        if((v_Token[i].TokenType == TokenType_Operator)&&(v_Token[i].TokenValue.OperatorType == OperatorType_Equal || v_Token[i].TokenValue.OperatorType ==  OperatorType_Unequal))
        {
            //乘法计算
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Equal)
            {
                tToken.TokenValue.NumberValue = abs(v_Token[i-1].TokenValue.NumberValue - v_Token[i+1].TokenValue.NumberValue)<0.000001;
            }
            //除法计算
            if(v_Token[i].TokenValue.OperatorType == OperatorType_Unequal)
            {
                tToken.TokenValue.NumberValue = abs(v_Token[i-1].TokenValue.NumberValue - v_Token[i+1].TokenValue.NumberValue)>0.000001;
            }
            v_Token[i] = tToken;
            v_Token.erase(v_Token.begin()+i -1);
            v_Token.erase(v_Token.begin()+i +1);
        }
    }
    if(1!=v_Token.size())
    {
        printf("RT_ScriptCalculatorError");
    }
    return v_Token[0].TokenValue.NumberValue;
}
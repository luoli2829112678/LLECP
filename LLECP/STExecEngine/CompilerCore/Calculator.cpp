#include"Calculator.h"
BaseToken Calculator(vector<BaseToken> vToken)
{
    BaseToken result;
    result.bInit = false;
    //先计算括号内的内容
    for (size_t i = 0; i < vToken.size(); i++)
    {
        if (vToken[i].enTokenType == TokenType_Delimiter)
        {
            int nHierarchy = 0;
            //匹配对应的括号
            if(vToken[i].KeywordAddr!=DelimiterType_Parentheses_L)
            {
                printf("括号匹配错误\n");
                break;
            }
            for (size_t j = i+1; j < vToken.size(); j++)
            {
                if(vToken[i].KeywordAddr!=DelimiterType_Parentheses_L)
                {
                    nHierarchy++;
                }
                if(vToken[i].KeywordAddr!=DelimiterType_Parentheses_R)
                {
                    nHierarchy--;
                    if(0 == nHierarchy)
                    {
                        //找到匹配括号，从i到j进行计算
                        vector<BaseToken> subExpr(
                            vToken.begin() + i + 1,
                            vToken.begin() + j   // 注意 +1，end 是开区间
                        );
                        //递归！
                        BaseToken subResult = Calculator(subExpr);
                        //用计算结果替换掉原来的那一串 token
                        vToken.erase(
                            vToken.begin() + i,
                            vToken.begin() + j + 1
                        );
                        vToken.insert(
                            vToken.begin() + i,
                            subResult
                        );
                        break;
                    }
                }
            }
            
        }
        
    }
    //再计算计算乘除法
    for (size_t i = 0; i < vToken.size(); i++)
    {
        if (vToken[i].enTokenType == TokenType_Operator)
        {
            //拿出两个Token进行计算
            BaseToken operand1 = vToken[i - 1];
            BaseToken operand2 = vToken[i + 1];
            
            result.enTokenType = TokenType_DOUBLENumber;
            //乘除法
            if (vToken[i].KeywordAddr == OperatorType_Ride)
            {
                result.KeywordAddr = operand1.KeywordAddr * operand2.KeywordAddr;
            }
            else if (vToken[i].KeywordAddr == OperatorType_Division)
            {
                result.KeywordAddr = operand1.KeywordAddr / operand2.KeywordAddr;
            }
            else
            {
                continue; // 不是乘除法，跳过
            }
            //替换掉原来的三个Token
            vToken.erase(
                vToken.begin() + i - 1,
                vToken.begin() + i + 2
            );
            vToken.insert(
                vToken.begin() + i - 1,
                result
            );
            i--; // 调整索引以继续处理
        }
    }
    //再计算加减法
    for (size_t i = 0; i < vToken.size(); i++)
    {
        if (vToken[i].enTokenType == TokenType_Operator)
        {
            //拿出两个Token进行计算
            BaseToken operand1 = vToken[i - 1];
            BaseToken operand2 = vToken[i + 1];
            result.enTokenType = TokenType_DOUBLENumber;
            //乘除法
            if (vToken[i].KeywordAddr == OperatorType_PLUS)
            {
                result.KeywordAddr = operand1.KeywordAddr + operand2.KeywordAddr;
            }
            else if (vToken[i].KeywordAddr == OperatorType_Division)
            {
                result.KeywordAddr = operand1.KeywordAddr - operand2.KeywordAddr;
            }
            else
            {
                continue; // 
            }
            //替换掉原来的三个Token
            vToken.erase(
                vToken.begin() + i - 1,
                vToken.begin() + i + 2
            );
            vToken.insert(
                vToken.begin() + i - 1,
                result
            );
            i--; // 调整索引以继续处理
        }
    }
    //大于小于计算
    for (size_t i = 0; i < vToken.size(); i++)
    {
        if (vToken[i].enTokenType == TokenType_Operator)
        {
            //拿出两个Token进行计算
            BaseToken operand1 = vToken[i - 1];
            BaseToken operand2 = vToken[i + 1];
            result.enTokenType = TokenType_INTNumber;
            //乘除法
            if (vToken[i].KeywordAddr == OperatorType_Greater)
            {
                result.KeywordAddr = operand1.KeywordAddr > operand2.KeywordAddr;
            }
            else if (vToken[i].KeywordAddr == OperatorType_Less)
            {
                result.KeywordAddr = operand1.KeywordAddr < operand2.KeywordAddr;
            }
            else
            {
                continue; 
            }
            //替换掉原来的三个Token
            vToken.erase(
                vToken.begin() + i - 1,
                vToken.begin() + i + 2
            );
            vToken.insert(
                vToken.begin() + i - 1,
                result
            );
            i--; // 调整索引以继续处理
        }
    }
    //等于计算
    for (size_t i = 0; i < vToken.size(); i++)
    {
        if (vToken[i].enTokenType == TokenType_Operator)
        {
            //拿出两个Token进行计算
            BaseToken operand1 = vToken[i - 1];
            BaseToken operand2 = vToken[i + 1];
            result.enTokenType = TokenType_INTNumber;
            //乘除法
            if (vToken[i].KeywordAddr == OperatorType_Equal)
            {
                result.KeywordAddr = operand1.KeywordAddr == operand2.KeywordAddr;
            }
            else if (vToken[i].KeywordAddr == OperatorType_Unequal)
            {
                result.KeywordAddr = operand1.KeywordAddr != operand2.KeywordAddr;
            }
            else
            {
                continue; //
            }
            //替换掉原来的三个Token
            vToken.erase(
                vToken.begin() + i - 1,
                vToken.begin() + i + 2
            );
            vToken.insert(
                vToken.begin() + i - 1,
                result
            );
            i--; // 调整索引以继续处理
        }
    }
    //与或非
    //返回结果
    result.bInit = true;
    return result;
}
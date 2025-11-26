#include"RT_Script.h"

ScriptUint_Cmd RT_ScriptSystem::RT_ScriptInterpreter(std::string sCmd,int& nRet)
{
    ScriptUint_Cmd cmd;
    std::vector<ScriptUint_Token>v_Token;
    std::vector<std::string>v_string;
    size_t i = 0;
    std::string t = "";
    bool Fs = false;
    //字符元素解析隔离
    while (i < sCmd.length()+1)
    {
        if(IsCharacter(sCmd[i])||IsNumber(sCmd[i]))
        {
            Fs = true;
            t += sCmd[i];
            i++;
            continue;
        }
        else
        {
            if(Fs)
            {
                Fs = false;
                v_string.push_back(t);
                t.clear();
            }
            t = sCmd[i];
            v_string.push_back(t);
            t.clear();
            i++;
            continue;
        }
    }
    //运算符合并
    for (size_t i = 0; i < v_string.size(); i++)
    {
        if(v_string[i] == ":")
        {
            if (v_string[i + 1] == "=")
            {
                v_string[i] = ":=";
                v_string.erase(v_string.begin() + i + 1);
            }
        }
        if(v_string[i] == ">")
        {
            if (v_string[i + 1] == "=")
            {
                v_string[i] = ">=";
                v_string.erase(v_string.begin() + i + 1);
            }
        }
        if(v_string[i] == "<")
        {
            if (v_string[i + 1] == "=")
            {
                v_string[i] = "<=";
                v_string.erase(v_string.begin() + i + 1);
            }
            if (v_string[i + 1] == ">")
            {
                v_string[i] = "<>";
                v_string.erase(v_string.begin() + i + 1);
            }
        }
        //清除空格
        if((v_string[i] == " "))
        {
            v_string.erase(v_string.begin() + i);
        }
    }
    v_string.pop_back();
    //字符解析
    for (size_t i = 0; i < v_string.size(); i++)
    {
        if(v_string[i] == ";")
            continue;
        ScriptUint_Token Token;
        //第一个字符为数字视为数字 负号视为数字，与运算符区分就是v_string[i].length()>1是为负数
        if(IsNumber(v_string[i][0]))
        {
            Token.TokenType = EN_TokenType::TokenType_Number;
            Token.TokenValue.NumberValue = std::stod(v_string[i]);
            v_Token.push_back(Token);
            continue;
        }
        //第一个为字符
        //已经声明的变量调用  2、函数 3、变量声明 4、逻辑语句 5、数据类型(原数据类型、结构体).通过:解决
        if(IsCharacter(v_string[i][0]))
        {
            //函数
            if(v_string[i+1] == "(")
            {
                Token = AnalysisToken_Function(v_string[i]);
                v_Token.push_back(Token);
                continue;
            }
            //3、变量声明直接执行处理了，不用执行的时候再处理了
            if(v_string[i+1] == ":")
            {
                Token = AnalysisToken_VariableType(v_string[i+2]);
                ScriptVariable Variable(Token.TokenValue.VariableType);
                VariableDeclaratio(nPushBufferIndex,v_string[i],Variable);
                ScriptUint_Cmd Tcmd;
                nRet = 1;
                return Tcmd;
            }
            //逻辑语句字符
            Token = AnalysisToken_LogicalStatement(v_string[i]);
            if(LogicalStatementType_NULL != Token.TokenValue.LogicalStatementType)
            {
                v_Token.push_back(Token);
                continue;
            }
            //已经声明的变量调用
            Token = AnalysisToken_Variable(v_string[i]);
            if(TokenType_Variable == Token.TokenType)
            {
                v_Token.push_back(Token);
                continue;
            }
            else
            {
                printf("-----------------------编译错误-----------------\n");
            }
        }
        //匹配是否是运算符
        Token = AnalysisToken_Operator(v_string[i]);
        if(OperatorType_NULL != Token.TokenValue.OperatorType)
        {
            v_Token.push_back(Token);
            continue;
        }
        //匹配分隔符
        Token = AnalysisToken_Delimiter(v_string[i]);
        if(OperatorType_NULL != Token.TokenValue.OperatorType)
        {
            v_Token.push_back(Token);
            continue;
        }
        //匹配赋值符号
        if(v_string[i] == sOp_ASSIGN) 
        {
            Token.TokenType = EN_TokenType::TokenType_Assignment;
            v_Token.push_back(Token);
            continue;
        }
    }
    cmd.v_Token = v_Token;
    cmd.bIsInit = true;
    return cmd;
}

bool RT_ScriptSystem::IsOperator(const char c)
{
    return m_sOperator.find(std::string(1, c)) != m_sOperator.end();
}

bool RT_ScriptSystem::IsVariable(const char c)
{
    return (c >= 'A' && c <= 'Z') ||   // 大写字母
           (c >= 'a' && c <= 'z') ||   // 小写字母
           (c >= '0' && c <= '9') ||   // 数字
           c == '_' ||                 // 下划线
           c == '[' ||                 // 左方括号
           c == ']';                   // 右方括号
}


EN_VariableType RT_ScriptSystem::IsVariableType(std::string str)
{
    if(s_BOOL == str)return  en_BOOL;
    if(s_UINT32 == str)return  en_UINT32;
    if(s_INT32 == str)return  en_INT32;
    if(s_DOUBLE == str)return  en_DOUBLE_64;
    return en_NULLType;
}

bool RT_ScriptSystem::IsCharacter(const char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}
bool RT_ScriptSystem::IsNumber(const char c)
{
    return (c >= '0' && c <= '9') || (c == '.');
}

ScriptUint_Token RT_ScriptSystem::AnalysisToken_Operator(std::string sToken)
{
    ScriptUint_Token Token;
    if (auto it = m_sOperator.find(sToken); it != m_sOperator.end()) {
        Token.TokenValue.OperatorType = it->second; 
        Token.TokenType = EN_TokenType::TokenType_Operator;
        return Token;
    }
    Token.TokenValue.OperatorType = EN_OperatorType::OperatorType_NULL;
    return Token;
}

ScriptUint_Token RT_ScriptSystem::AnalysisToken_Variable(std::string sToken)
{
    //先从全局变量寻找，再从局部变量寻找
    ScriptUint_Token Token;
    Token.nRemarks = -2;
    if (auto it = m_ScriptVariableGlobal.find(sToken); it != m_ScriptVariableGlobal.end()) 
    {
        Token.TokenType = EN_TokenType::TokenType_Variable;
        Token.TokenValue.KeywordAddr = std::distance(m_ScriptVariableGlobal.begin(), it);
        Token.nRemarks = -1;
    }

    if (auto it = m_ScriptVariableBuffer[nPushBufferIndex].find(sToken); it != m_ScriptVariableBuffer[nPushBufferIndex].end()) 
    {
        Token.TokenType = EN_TokenType::TokenType_Variable;
        Token.TokenValue.KeywordAddr = std::distance(m_ScriptVariableBuffer[nPushBufferIndex].begin(), it);
        Token.nRemarks = nPushBufferIndex;
    }
    return Token;
}

ScriptUint_Token RT_ScriptSystem::AnalysisToken_Function(std::string sToken)
{
    ScriptUint_Token Token;
    Token.TokenType = EN_TokenType::TokenType_Function;
    return Token;
}

ScriptUint_Token RT_ScriptSystem::AnalysisToken_Delimiter(std::string sToken)
{
    ScriptUint_Token Token;
    if (auto it = m_sDelimiter.find(sToken); it != m_sDelimiter.end()) {
        Token.TokenType = EN_TokenType::TokenType_Delimiter;
        Token.TokenValue.DelimiterType = it->second; 
        return Token;
    }
    Token.TokenValue.DelimiterType = EN_DelimiterType::DelimiterType_NULL;
    return Token;
}

ScriptUint_Token RT_ScriptSystem::AnalysisToken_LogicalStatement(std::string sToken)
{
    ScriptUint_Token Token;
    if (auto it = m_sLogicalStatement.find(sToken); it != m_sLogicalStatement.end()) {
        Token.TokenType = EN_TokenType::TokenType_LogicalStatement;
        Token.TokenValue.LogicalStatementType = it->second; 
        return Token;
    }
    Token.TokenValue.LogicalStatementType = EN_LogicalStatementType::LogicalStatementType_NULL;
    return Token;
}

ScriptUint_Token RT_ScriptSystem::AnalysisToken_VariableType(std::string sToken)
{
    ScriptUint_Token Token;
    if (auto it = m_sVariableType.find(sToken); it != m_sVariableType.end()) {
        Token.TokenValue.VariableType = it->second; 
        Token.TokenType = EN_TokenType::TokenType_VariableType;
        return Token;
    }
    Token.TokenValue.VariableType = EN_VariableType::en_NULLType;
    return Token;
}

int RT_ScriptSystem::VariableDeclaratio(int16_t bufferindex,std::string sVarName, ScriptVariable var)
{
    if(bufferindex>SCRIPTNUMBUFF_MAX)
    {
        return -1;
    }
    if(0 > bufferindex)
    {
        m_ScriptVariableGlobal.emplace(sVarName,var);
    }
    else
    {
        m_ScriptVariableBuffer[bufferindex].emplace(sVarName,var);
    }
    return 0;
}
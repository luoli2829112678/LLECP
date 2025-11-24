#include"Parser.h"

Parser::Parser(VariableManager* pVariableManager,StructManager* pStructManager,FunctionManager* pFunctionManager)
{
    m_pFunctionManager = pFunctionManager;
    m_pStructManager = pStructManager;
    m_pVariableManager = pVariableManager;
}

Parser::~Parser()
{
}

bool Parser::IsCharacter(const char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}

bool Parser::IsNumber(const char c)
{
    return (c >= '0' && c <= '9') || (c == '.');
}

int Parser::ParserCmd(string sCmd,CmdUint &stCmdUint)
{
    //分割字符串
    vector<string> v_scmd = SplitString(sCmd);

    return 0;
}

vector<string> Parser::SplitString(string cmd)
{
    vector<string> result;
    size_t i = 0;

    while (i < cmd.size()) {

        // 跳过空格
        if (isspace(cmd[i])) { 
            i++; 
            continue; 
        }

        bool matched = false;

        // ① 先尝试匹配多字符符号（按列表顺序）
        for (const auto& sym : symbols) {
            size_t len = sym.size();
            if (i + len <= cmd.size() && cmd.substr(i, len) == sym) {
                result.push_back(sym);
                i += len;
                matched = true;
                break;
            }
        }

        if (matched) 
            continue;

        // 如果不是符号，则解析连续的标识符或数字
        if (isalnum(cmd[i]) || cmd[i] == '_') {
            size_t start = i;
            while (i < cmd.size() && (isalnum(cmd[i]) || cmd[i] == '_'))
                i++;
            result.push_back(cmd.substr(start, i - start));
        }
        else {
            // 其它未知字符（可以继续扩展）
            result.push_back(string(1, cmd[i]));
            i++;
        }
    }

    //去除空格与结束符
    for (size_t i = 0; i < result.size(); i++)
    {
        if((SYM_SPACE == result[i]) || (SYM_SEMICOLON == result[i]))
        {
            result.erase(result.begin() + i);
        }
    }
    
    return result;
}



BaseToken LogicalStatement_Parse(string cmd)
{
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = true;
    if(sCmd_IF == cmd)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_IF;
    }
    else if (cmd == sCmd_THEN)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_THEN;
    }
    else if (cmd == sCmd_ELSIF)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_ELSIF;
    }
    else if (cmd == sCmd_ELSE)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_ELSE;
    }
    else if (cmd == sCmd_END_IF)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_END_IF;
    }
    else if (cmd == sCmd_WHILE)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_WHILE;
    }
    else if (cmd == sCmd_END_WHILE)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_END_WHILE;
    }
    else if (cmd == sCmd_DO)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_DO;
    }
    else if (cmd == sCmd_FOR)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_FOR;
    }
    else if (cmd == sCmd_END_FOR)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_END_FOR;
    }
    else if (cmd == sCmd_TO)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_TO;
    }
    else if (cmd == sCmd_BY)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_BY;
    }
    else if (cmd == sCmd_CASE)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_CASE;
    }
    else if (cmd == sCmd_OF)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_OF;
    }
    else if (cmd == sCmd_END_CASE)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_END_CASE;
    }
    else if (cmd == sCmd_REPEAT)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_REPEAT;
    }
    else if (cmd == sCmd_UNTIL)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_UNTIL;
    }
    else if (cmd == sCmd_END_REPEAT)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_END_REPEAT;
    }
    else if (cmd == sCmd_EXIT)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_EXIT;
    }
    else if (cmd == sCmd_RETURN)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_RETURN;
    }
    else if (cmd == sCmd_CONTINUE)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_CONTINUE;
    }
    else if (cmd == sCmd_DEFAULT)
    {
        T_Token.enTokenType = TokenType_LogicalStatement;
        T_Token.KeywordAddr = LogicalStatementType_DEFAULT;
    }
    else
    {
        T_Token.bInit = false;
    }
    return T_Token;
}
BaseToken Parser::BoolLiteral_Parse(string cmd)
{
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = true;
    if((BOOL_TRUE == cmd)||(BOOL_true == cmd))
    {
        T_Token.enTokenType = TokenType_INTNumber;
        T_Token.KeywordAddr = true;
    }
    else if ((BOOL_FALSE == cmd)||(BOOL_false == cmd))
    {
        T_Token.enTokenType = TokenType_INTNumber;
        T_Token.KeywordAddr = false;
    }
    else
    {
        T_Token.bInit = false;
    }
    return T_Token;
}
BaseToken Parser::Preprocessing_Parse(string cmd)
{
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = true;
    //第一个是字符则视为是的，因此这个函数要放在LogicalStatement_Parse等函数后
    if(IsCharacter(cmd[0]))
    {
        T_Token.enTokenType = TokenType_Preprocessing;
        T_Token.KeywordAddr = false;
    }
    else
    {
        T_Token.bInit = false;
    }
    return T_Token;
}
BaseToken Parser::Assignment_Parse(string cmd)
{
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = true;
    if(SYM_ASSIGN == cmd)
    {
        T_Token.enTokenType = TokenType_Assignment;
        T_Token.KeywordAddr = false;
    }
    else
    {
        T_Token.bInit = false;
    }
    return T_Token;
}
BaseToken Parser::Delimiter_Parse(string cmd)
{
    //ST分隔符只有逗号
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = true;
    if(SYM_COMMA == cmd)
    {
        T_Token.enTokenType = TokenType_COMMA;
        T_Token.KeywordAddr = false;
    }
    else
    {
        T_Token.bInit = false;
    }
    return T_Token;
}

BaseToken Parser::Number_Parse(string cmd)
{
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = false;

    size_t i = 0;
    bool hasDot = false;
    bool hasDigit = false;
    for (; i < cmd.size(); ++i)
    {
        char c = cmd[i];

        if (std::isdigit((unsigned char)c))
        {
            hasDigit = true;
        }
        else if (c == '.')
        {
            if (hasDot) return T_Token; // 不能出现多个小数点
            hasDot = true;
        }
        else
        {
            return T_Token;
        }
    }

    if (!hasDigit)
        return T_Token;
    T_Token.bInit = true;
    if(hasDigit)
    {
        T_Token.enTokenType = TokenType_DOUBLENumber;
        T_Token.KeywordAddr = stod(cmd);;
    }
    else
    {
        T_Token.enTokenType = TokenType_INTNumber;
        T_Token.KeywordAddr = stoi(cmd);;
    }
    return T_Token;
}
BaseToken Parser::Operator_Parse(string cmd)
{
    BaseToken T_Token;
    T_Token.KeywordAddr = -1;
    T_Token.bInit = true;
    if(SYM_LE == cmd)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_LessEqual;
    }
    else if (cmd == SYM_GE)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_GreaterEqual;
    }
    else if (cmd == SYM_NE)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Unequal;
    }
    else if (cmd == SYM_PLUS)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_PLUS;
    }
    else if (cmd == SYM_MINUS)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Subtract;
    }
    else if (cmd == SYM_MUL)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Ride;
    }
    else if (cmd == SYM_DIV)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Division;
    }

    else if (cmd == SYM_GT)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Greater;
    }
    else if (cmd == SYM_LT)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Less;
    }
    else if (cmd == SYM_EQ)
    {
        T_Token.enTokenType = TokenType_Operator;
        T_Token.KeywordAddr = OperatorType_Equal;
    }
    else
    {
        T_Token.bInit = false;
    }
    return T_Token;
}

BaseToken Parser::VariableType_Parse(string cmd)
{

}

BaseToken Parser::Function_Parse(string cmd)
{

}
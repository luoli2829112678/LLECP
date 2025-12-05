#include"STExecEngine.h"

int main() {
    std::vector<std::string> v_codes = {
        "INT x;",
        "x := 0;",
        "x := 1;",
        "x := 2;",
        "IF (x+1) > 10 THEN",
        "x := 5;",
        "x := 7;",
        "ELSE",
        "x := 100;",
        "x := 200;",
        "END_IF;",
        "x := 1000;",
    };

    std::vector<antlr4::CommonTokenStream*> v_tokens; 
    std::vector<antlr4::ANTLRInputStream*> v_input;
    std::vector<STGrammarLexer*> v_lexer; 
    for (size_t i = 0; i < v_codes.size(); i++) 
    { 
        const std::string &code = v_codes[i];
        v_input.push_back(new antlr4::ANTLRInputStream(code));
        v_lexer.push_back(new STGrammarLexer(v_input[i]));
        antlr4::CommonTokenStream* ptoken = new antlr4::CommonTokenStream(v_lexer[i]); 
        v_tokens.push_back(ptoken); 
    }
    EvalVisitor ev;
    for (size_t i = 0; i < v_tokens.size(); ++i)
    { 
        for (size_t j = 0; j < v_tokens[i]->getTokens().size(); j++) 
        {
            std::cout<<v_tokens[i]->getTokens()[j]->getText()<< std::endl; ;
        } 
        STGrammarParser parser(v_tokens[i]); auto *stmt = parser.statement(); 
        ev.visit(stmt); 
        // ===== 特定行打印 x ===== 
        auto it = ev.vars.find("x"); 
        if (it != ev.vars.end())
        { 
            std::cout << "执行 \"" << v_codes[i] << "\" 后: x = " << it->second.toString() << std::endl; 
        } 
    } 
    return 0; 
}

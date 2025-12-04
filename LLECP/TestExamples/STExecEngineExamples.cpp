#include"STExecEngine.h"
int main() {
    std::vector<std::string> v_codes = {
        "INT x;",
        "x := 0;",
        "x := 1;",
        "x := 2;",
        "IF (x+1) > 1 THEN x := 2; END_IF;"
    };

    EvalVisitor ev;

    for (size_t i = 0; i < v_codes.size(); ++i) {
        const std::string &code = v_codes[i];

        antlr4::ANTLRInputStream input(code);
        STGrammarLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        STGrammarParser parser(&tokens);

        auto *stmt = parser.statement();
        ev.visit(stmt);

        // ===== 特定行打印 x =====
        if (i == 1 || i == 2) {
            auto it = ev.vars.find("x");
            if (it != ev.vars.end()) {
                std::cout << "执行 \"" << code << "\" 后: x = "
                          << it->second.toString() << std::endl;
            }
        }
    }
    return 0;
}
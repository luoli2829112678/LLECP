#pragma once

// 多字符符号（必须优先匹配）
#define SYM_ASSIGN      ":="
#define SYM_LE          "<="
#define SYM_GE          ">="
#define SYM_NE          "<>"
#define SYM_RANGE       ".."

// 单字符符号
#define SYM_PLUS        "+"
#define SYM_MINUS       "-"
#define SYM_MUL         "*"
#define SYM_DIV         "/"
#define SYM_GT          ">"
#define SYM_LT          "<"
#define SYM_EQ          "="
#define SYM_SPACE       " "
#define SYM_LPAREN      "("
#define SYM_RPAREN      ")"
#define SYM_COMMA       ","
#define SYM_SEMICOLON   ";"
#define SYM_COLON       ":"

#define SYM_Bracket_L         '['
#define SYM_Bracket_R         ']'
#define SYM_Braces_L          "{"
#define SYM_Braces_R          "}"
#define SYM_COMMA      ","

#define sCmd_IF             "IF"
#define sCmd_THEN           "THEN"
#define sCmd_ELSIF          "ELSIF"
#define sCmd_ELSE           "ELSE"
#define sCmd_END_IF         "END_IF"
#define sCmd_DO              "DO"
#define sCmd_BY              "BY"
#define sCmd_WHILE           "WHILE"
#define sCmd_FOR           "FOR"
#define sCmd_END_FOR        "END_FOR"
#define sCmd_END_WHILE       "END_WHILE"
#define sCmd_TO             "TO"
#define sCmd_CASE           "CASE"
#define sCmd_OF             "OF"
#define sCmd_END_CASE       "END_CASE"
#define sCmd_REPEAT         "REPEAT"
#define sCmd_UNTIL          "UNTIL"
#define sCmd_END_REPEAT     "END_REPEAT"
#define sCmd_EXIT           "EXIT"
#define sCmd_RETURN         "RETURN"
#define sCmd_CONTINUE       "CONTINUE"
#define sCmd_DEFAULT        "DEFAULT"


#define s_BOOL             "BOOL"
#define s_UINT32            "UDINT"
#define s_INT32             "DINT"
#define s_DOUBLE            "LREAL"
#define s_STRING            "STRING"


#define BOOL_TRUE           "TRUE"
#define BOOL_FALSE           "FALSE"
#define BOOL_true           "true"
#define BOOL_false           "false"

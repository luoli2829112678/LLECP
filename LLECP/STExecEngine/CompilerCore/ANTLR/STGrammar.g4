grammar STGrammar;

// 词法规则（Lexer Rules）
WS              : [ \t]+ -> skip;  // 忽略空白字符
NEWLINE         : '\r'? '\n';
COMMENT         : '(*' .*? '*)' -> skip;  // 多行注释
LINE_COMMENT    : '//' ~[\r\n]* -> skip;  // 单行注释
COMMA            : ',' ;
SEMI            : ';' ;

// 数据类型和标识符
BOOL            : 'TRUE' | 'FALSE';
INT             : [1-9][0-9]*
                | '0'
                ;
fragment DIGIT  : [0-9];    // 匹配单个数字
LREAL           : [1-9][0-9]* '.' DIGIT*    // 1.39、3.14159等
                | '0'*'.' DIGIT+           // .12 (表示0.12)
                ;

// 基本数据类型
INT_TYPE        : 'INT' ;
LREAL_TYPE       : 'LREAL';
BOOL_TYPE       : 'BOOL';



// 关键字
IF              : 'IF';
THEN            : 'THEN';
ELSE            : 'ELSE';
ELSE_IF         : 'ELSIF';
END_IF          : 'END_IF';
//FOR             : 'FOR';
TO              : 'TO';
DO              : 'DO';
END_FOR         : 'END_FOR';
ASSIGN          : ':=';  // 赋值运算符
// VAR             : 'VAR';
// VAR_GLOBAL      : 'VAR_GLOBAL';
// END_VAR         : 'END_VAR';
BY              : 'BY';
LOOP            : 'LOOP';
END_LOOP        : 'END_LOOP';
TILL            : 'TILL';
BLOCK           : 'BLOCK';
END_BLOCK       : 'END_BLOCK';

// 运算符
MULT            : '*';
DIV             : '/';
PLUS            : '+';
MINUS           : '-';
AND             : 'AND';
OR              : 'OR';
NOT             : 'NOT';
EQ              : '=';
NEQ              : '@';
GT              : '>';
LT              : '<';

AXIS_ENABLE       : 'AXIS_ENABLE';
AXIS_DISABLE      : 'AXIS_DISABLE';
AXIS_STOP         : 'AXIS_STOP';
AXIS_MOVE_ABS     : 'AXIS_MOVE_ABS';
AXIS_MOVE_REL     : 'AXIS_MOVE_REL';
AXIS_MOVE_VEL     : 'AXIS_MOVE_VEL';
AXIS_POS          : 'AXIS_POS';
AXIS_VEL          : 'AXIS_VEL';
AXIS_ACC          : 'AXIS_ACC';
AXIS_JERK         : 'AXIS_JERK';
AXIS_DEC          : 'AXIS_DEC';
AXIS_RESET        : 'AXIS_RESET';

AXIS_STAUTS_STATE   : 'AXIS_STAUTS_STATE';
AXIS_STAUTS_ENABLE  : 'AXIS_STAUTS_ENABLE';
AXIS_STAUTS_MOVE    : 'AXIS_STAUTS_MOVE';

DRIVE_SET_DO      : 'DRIVE_SET_DO';
DRIVE_SET_AO      : 'DRIVE_SET_AO';
DRIVE_STAUTS_DI   : 'DRIVE_STAUTS_DI';
DRIVE_STAUTS_AI   : 'DRIVE_STAUTS_AI';

BUFFER_ENABLE     : 'BUFFER_ENABLE';
BUFFER_DISABLE    : 'BUFFER_DISABLE';

WAIT              : 'WAIT';
NULL_CMD          : 'NULL_CMD';

START_ANALOGFOCUSING  : 'START_ANALOGFOCUSING';
STOP_ANALOGFOCUSING   : 'STOP_ANALOGFOCUSING';
START_PEG             : 'START_PEG';
STOP_PEG              : 'STOP_PEG';

one_para_set_func_name   : AXIS_ENABLE
                        | AXIS_DISABLE
                        | AXIS_STOP
                        | AXIS_MOVE_ABS
                        | AXIS_MOVE_REL
                        | AXIS_MOVE_VEL
                        | AXIS_RESET
                        | WAIT
                        | BUFFER_ENABLE
                        | BUFFER_DISABLE
                        | START_ANALOGFOCUSING
                        | STOP_ANALOGFOCUSING
                        | START_PEG
                        | STOP_PEG
                        ;
two_para_set_func_name   : AXIS_POS
                        | AXIS_VEL
                        | AXIS_ACC
                        | AXIS_JERK
                        | AXIS_DEC
                        | DRIVE_SET_DO
                        | DRIVE_SET_AO
                        ;

read_func_name  : AXIS_STAUTS_STATE
                | AXIS_STAUTS_ENABLE
                | AXIS_STAUTS_MOVE
                | DRIVE_STAUTS_DI
                | DRIVE_STAUTS_AI
                ;

ID              : [a-zA-Z_][a-zA-Z0-9_]*;  // 变量名，标识符，放到最后定义，避免把关键字识别成ID

// 语法规则（Parser Rules）
program         : statement+EOF;

statement       : (assignment | if_statement | global_var_decl | one_para_function|two_para_function| read_set_function | loop_statement | block_statement |till_statement) SEMI (NEWLINE+ | EOF);

//赋值语句
assignment      : ID ASSIGN expression;  // e.g., x := y + 1;
//表达式
expression      : expression (PLUS | MINUS | MULT | DIV) expression  # BinaryOp
                | expression (AND | OR ) expression            # LogicalOp
                | NOT expression                                     # NotOp
                | ID                                                 # Var
                | INT                                                # Const
                | BOOL                                               # BoolConst
                | LREAL                                               # LREAL
                | '(' expression ')'                                # ParenExpr
                | one_para_function                                 # Set1PFuncExpr
                | two_para_function                                 # Set2PFuncExpr
                | read_set_function                                 # ReadFuncExpr;

//if语法
if_statement    : IF condition THEN NEWLINE+ statement+ ((ELSE_IF condition THEN NEWLINE+ statement+)*)(ELSE NEWLINE+ statement)? END_IF;
//条件
condition       : expression (EQ |NEQ| GT | LT | AND | OR ) expression | BOOL;

//for语法
//for_statement   : FOR ID ASSIGN INT TO INT (BY INT)? DO NEWLINE+ statement+ END_FOR;

// 全局变量声明（作用域为整个程序）
global_var_decl : INT_TYPE ID (ASSIGN INT)? 
                | BOOL_TYPE ID (ASSIGN BOOL)? 
                | LREAL_TYPE ID (ASSIGN LREAL)? ;

// 调用函数
//call_function   : ID '(' argumentList? ')' ; // 函数名 + 括号 + 可选参数列表
//call_set_function   : set_func_name '(' argumentList? ')' ; // 函数名 + 括号 + 可选参数列表
one_para_function   : one_para_set_func_name'(' expression ')' ;
two_para_function   : two_para_set_func_name'(' expression '#'expression')' ;
read_set_function   : read_func_name '[' expression ']' ; // 函数名 + 括号 + 可选参数列表
argumentList    : expression ('#' expression)* ; // 参数列表（逗号分隔的表达式）

loop_statement  : LOOP INT THEN NEWLINE+ statement+ END_LOOP ;
till_statement  : TILL '('condition')' ;

block_statement : BLOCK NEWLINE+ statement+ END_BLOCK ;




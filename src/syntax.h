#pragma once

typedef enum EExpression {
    EEXPRESSION_SCOPE,
    EEXPRESSION_ADD,
    EEXPRESSION_SUBSTRACT,
    EEXPRESSION_RETURN,
    EEXPRESSION_TREE,
} EExpression;

typedef struct Syntax_Expression {
    EExpression type;
    union
    {
        struct {
            struct Syntax_Expression* begin;
            struct Syntax_Expression* end;
        } subExpr;

        struct {
            int a, b;
            char operator;
        } binaryOp;

        struct Syntax_Expression* returnExpr;
    } data;
} Syntax_Expression;

typedef struct Syntax_FunctionParam {
    const char* name;
} Syntax_FunctionParam;

typedef struct Syntax_Function {
    const char* name;
    Syntax_FunctionParam* params;
    //Syn
} Syntax_Function;

typedef struct Syntax_Program {
    int compiledOk;
    Syntax_Function* functions;
} Syntax_Program;

typedef struct Syntax_ParseState {

} Syntax_ParseState;
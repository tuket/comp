#pragma once

#include <utils.h>

namespace tkc
{

namespace ast
{

enum class ENode {
    FUNC_DECL,
    STRUCT_DECL,
    ENUM_DECL,
    STATEMENT,

    EXPR,
    ADD,
    SUB,
    MULT,
    DIV,

    MEMBER_ACCESS,
    ARRAY_ACCESS,

    IDENTIFIER,

    LITERAL_INT,
    LITERAL_REAL,
    LITERAL_STRING,
};

enum class EStatement {
    IF,
    RETURN,
    BREAK,
    CONTINUE,
    DECL,
    FOR,
    WHILE
}

struct Node;
struct Statement;

struct Statement_if {
    Node_Expr* condition;
    Node* ifBody;
    Node* elseBody;
};

struct Statement_return {
    Node* body;
};

struct Statement_decl {
    Node* type;
    const char* varName;
}

struct Statement {
    EStatement type;
    union {
        Statement_if s_if;
        Statement_return s_return;
        Statement_decl s_decl;
    }
}

struct Node_Statement {
    
}

struct Node_FuncParam {
    const char* name;
    const char* typeName;
};

struct Node_FuncOut {
    const char* name = nullptr;
    const char* typeName;
};

struct Node_FuncBody {
    Span<AstNode_Statement> statements;
}

struct Node_FuncDecl {
    const char* name;
    Span<Node_FuncParam> params;
    Span<Node_FuncOut> outs;
    Node_FuncBody* body;
};

struct Node {

};

}

}
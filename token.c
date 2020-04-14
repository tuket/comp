#include <stdio.h>
#include <assert.h>

typedef enum {
    ETOKEN_NUMBER,

    ETOKEN_PLUS,
    ETOKEN_MINUS,

    ETOKEN_END,

    ETOKEN_COUNT,
    ETOKEN_ERROR
} EToken;

typedef struct {
    EToken type;
    int valInt;
} Token;

typedef int (*TokenizeCallback)(Token, int, void*);

int isNumChar(char c)
{
    return c >= '0' && c <= '9';
}

int isTokenOperator(EToken et)
{
    return et == ETOKEN_PLUS || et == ETOKEN_MINUS;
}

int tokenize(TokenizeCallback callback, const char* str, void* userData)
{
    int line = 1;
    int keepRunning = 1;
    for(const char* c = str; keepRunning && *c; )
    {
        if(isNumChar(*c)) {
            int num = *c - '0';
            for(c++; c && isNumChar(*c); c++) {
                num *= 10;
                num += *c;
            }
            keepRunning = callback((Token){ETOKEN_NUMBER, num}, line, userData);
        }
        else if(*c == '+') {
            keepRunning = callback((Token){ETOKEN_PLUS}, line, userData);
            c++;
        }
        else if(*c == '-') {
            keepRunning = callback((Token){ETOKEN_MINUS}, line, userData);
            c++;
        }
        else if(*c == ' ' || *c == '\t') {
            c++;
        }
        else if(*c == '\n') {
            c++;
            line++;
        }
        else {
            keepRunning = callback((Token){ETOKEN_ERROR}, line, userData);
            return 0;
        }
    }
    callback((Token){ETOKEN_END}, line, userData);
    return 1;
}

// ----------------------------------------------------------------------------------------------

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

int syntax_onToken(Token token, int line, void* userData)
{

}

Syntax_Program generateSyntaxTree(const char* str)
{
    Syntax_ParseState state = {

    };
    tokenize(syntax_onToken, str, &state);
}

// ----------------------------------------------------------------------------------------------

char* syntaxToCCode(const Syntax_Program* syn)
{

}

// ----------------------------------------------------------------------------------------------

void printTokenCallback(Token token, int line, void* userData)
{
    if(token.type == ETOKEN_NUMBER) {
        printf("number: %d\n", token.valInt);
    }
    else if(token.type == ETOKEN_PLUS) {
        printf("plus\n");
    }
    else if(token.type == ETOKEN_MINUS) {
        printf("minus\n");
    }
    else if(token.type == ETOKEN_ERROR) {
        printf("error\n");
    }
    else {
        printf("unknown\n");
    }
}

typedef struct SimpleCalculatorData {
    int currentVal;
    char operator;
} SimpleCalculatorData;

int simpleCalculatorCallback(Token token, int line, void* userData)
{
    SimpleCalculatorData* data = userData;
    if(token.type == ETOKEN_NUMBER) {
        if(data->operator) {
            if(data->operator == '+')
                data->currentVal += token.valInt;
            else if(data->operator == '-')
                data->currentVal -= token.valInt;
            data->operator = 0;
        }
        else {
            data->currentVal = token.valInt;
        }
    }
    else if(isTokenOperator(token.type)) {
        if(data->operator) {
            printf("error(%d): two operators\n", line);
            return 0;
        }
        if(token.type == ETOKEN_PLUS)
            data->operator = '+';
        else if(token.type == ETOKEN_MINUS)
            data->operator = '-';
        else
            assert(0 && "fail in the compiler");
    }
    else if(token.type == ETOKEN_END) {
        printf("result: %d\n", data->currentVal);
    }
    return 1;
}

int main()
{
    const char* testStr = "2+2";
    SimpleCalculatorData calcData = {
        .currentVal = 0,
        .operator = 0
    };
    tokenize(simpleCalculatorCallback, testStr, &calcData);
}
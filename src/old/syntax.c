#include "syntax.h"

int syntax_onToken(Token token, int line, void* userData)
{

}

Syntax_Program generateSyntaxTree(const char* str)
{
    Syntax_ParseState state = {

    };
    tokenize(syntax_onToken, str, &state);
}
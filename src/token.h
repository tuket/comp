#pragma once

#include <stddef.h>
#include <stdint.h>

typedef enum {
    ETOKEN_INT_LITERAL,
    ETOKEN_FLOAT_LITERAL,
    ETOKEN_STRING_LITERAL,
    
    ETOKEN_INT,
    ETOKEN_UINT,
    ETOKEN_FLOAT,
    ETOKEN_I8,
    ETOKEN_I16,
    ETOKEN_I32,
    ETOKEN_I64,
    ETOKEN_U8,
    ETOKEN_U16,
    ETOKEN_U32,
    ETOKEN_U64,
    
    ETOKEN_IDENTIFIER,
    ETOKEN_PUBLIC,
    ETOKEN_VAR,
    ETOKEN_FUNC,
    ETOKEN_ALPHANUM,
    ETOKEN_ARROW,
    
    ETOKEN_OPEN_PARENTH,
    ETOKEN_CLOSE_PARENTH,
    ETOKEN_OPEN_CURLY,
    ETOKEN_CLOSE_CURLY,
    
    ETOKEN_ASIGN_DECL,
    ETOKEN_ASIGN,
    
    ETOKEN_PLUS,
    ETOKEN_MINUS,
    ETOKEN_STAR,
    ETOKEN_SLASH,
    
    ETOKEN_DOT,
    ETOKEN_COMMA,
    ETOKEN_SEMICOLON,

    ETOKEN_END,

    ETOKEN_COUNT,
    ETOKEN_ERROR
} EToken;

typedef struct {
    EToken type;
    int valInt;
} Token;

typedef struct TokenizationStrings_Bucket {
    char* strs[8];
} TokenizationStrings_Bucket;

typedef struct TokenizationStrings {
    char* buffer;
    size_t bufferSize;
    TokenizationStrings_Bucket* buckets;
    size_t numBuckets;
} TokenizationStrings;

size_t findTokenizationString(TokenizationStrings* data, const char* str);

typedef int (*TokenizeCallback)(Token, int, void*);
#pragma once

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
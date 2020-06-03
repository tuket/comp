#include "token.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static inline int isNum        (char c) { return c >= '0' && c <= '9'; }
static inline int isAlpha      (char c) { return c >= 'A' && c <= 'z'; }
static inline int isAlphaNum   (char c) { return isAlpha(c) || isNum(c); }
static inline int isAlphaU     (char c) { return isAlpha(c) || c == '_'; }
static inline int isAlphaNumU  (char c) { return isAlphaNum(c) || c == '_'; }
static inline int isSpace      (char c) { return c == ' ' || c == '\t' || c == '\n'; }

static inline int matchStrS(const char* str, const char* pattern)
{
    int count = 1;
    for(const char *s = str, *p = pattern; ; s++, p++, count++)
    {
        if(*s == 0)
            return *p == 0 ? count : 0;
        if(*p == 0)
            return *s == 0 || isSpace(*s) ? count : 0;
        if(isSpace(*s))
            return 0;
    }
}

int tokenize(TokenizeCallback callback, const char* str, void* userData)
{
    int line = 1;
    int keepRunning = 1;
    for(const char* c = str; keepRunning && *c; )
    {
        if(isNum(*c)) {
            int num = *c - '0';
            for(c++; c && isNum(*c); c++) {
                num *= 10;
                num += *c;
            }
            if(*c == '.') {
                assert(0 && "not implemented");
                int decimalPart = 0;
                for(c++; c && isNum(*c); c++) {
                    decimalPart *= 10;
                    decimalPart += *c;
                }
            }
            else {
                keepRunning = callback((Token){ETOKEN_INT_LITERAL, num}, line, userData);
            }
        }
        else if(isAlphaU(*c)) {
            Token token;
            int skip = 0;
            if(*c == 'i') {
                if(skip = matchStrS(c+1, "nt"))
                    token.type = ETOKEN_INT;
            }
            else if(*c == 'u') {
                
            }
            else if(*c == 'f') {
                
            }
            else if(*c == 'v') {
                
            }
            else if(*c == 'p') {
                
            }
            if(skip) { // we have found a match for a reserved keyword
                c += skip;
                callback(token, line, userData);
            }
            else { // it's some identifier
                token.type = ETOKEN_IDENTIFIER;
                //TODO
            }
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

/*void printTokenTestCallback(Token token, int line, void* userData)
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
}*/

TokenizationStrings createTokenizationStrings(size_t size)
{
    TokenizationStrings data;
    data.bufferSize = size;
    data.buffer = malloc(size);
    memset(data.buffer, size, 0);
    return data;
}

// Tries to find str. If found, returns the offset. If not found, returns where it should be inserted
size_t findTokenizationString(TokenizationStrings* data, const char* str)
{
    const size_t strLen = strlen(str);
    char* buffer = data->buffer;
    size_t i = 0;
    while(i < data->bufferSize)
    {
        const u16 len = *(u16*)(buffer+i);
        if(len == 0)
            return i;
        if(len == strLen && strcmp(str, buffer+i+2) == 0)
            return i;
        i += len+3;
    }
    return data->bufferSize;
}

// Check if the return value of the previous function is a valid
static inline size_t findTokenizationStringHelper_isValid(TokenizationStrings* data, size_t offset)
{
    return data->bufferSize != offset &&
           ((u16*)data->buffer + offset)[0] != 0;
}

size_t addTokenizationString(TokenizationStrings* data, const char* str)
{
    const size_t offset = findTokenizationString(data, str);
    if(findTokenizationStringHelper_isValid(data, offset))
        return offset;
    const u16 strLen = strlen(str);
    const size_t requiredSpace = strLen + 3;
    const size_t occupiedSpace = offset;
    const size_t remainingSpace = data->bufferSize - occupiedSpace;
    if(requiredSpace > remainingSpace) {
        size_t newSize = MAX(data->bufferSize * 2, occupiedSpace + requiredSpace);
        char* newBuffer = malloc(newSize);
        memcpy(newBuffer, data->buffer, occupiedSpace);
        free(data->buffer);
        data->bufferSize = newSize;
        data->buffer = newBuffer;
        const size_t newOccupiedSpace = occupiedSpace + requiredSpace;
        memset(data->buffer + newOccupiedSpace, newSize - newOccupiedSpace, 0);
    }
    *(u16*)(data->buffer + occupiedSpace) = strLen;
    strcpy(data->buffer + occupiedSpace + 2, str);
    return occupiedSpace;
}

char* getTokenizationString(TokenizationStrings* data, size_t offset)
{
    return data->buffer + offset + 2;
}

void _testTokenizationStrings()
{
    const char* strs[] = {
        "ab", "bb", "cc", "cc", "aa",
        "cb", "cc", "cb", "cb", "ba",
        "aa", "ba", "cc", "ca", "aa",
        "bc", "bc", "ca", "cc", "ab"
    };
    TokenizationStrings data = createTokenizationStrings(12);
    const int n = sizeof(strs) / sizeof(char*);
    size_t offsets[n];
    for(int i = 0; i < n; i++)
        offsets[i] = addTokenizationString(&data, strs[i]);
    for(int i = 0; i < n; i++) {
        size_t offset = findTokenizationString(&data, strs[i]);
        char* str = getTokenizationString(&data, offset);
        if(strcmp(strs[i], str) != 0)
            printf("failed at %d, expected: %s, got: %s\n", i, strs[i], str);
    }
}
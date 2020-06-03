#include "utils.h"
#include <stdlib.h>
#include <assert.h>

char* readStringFromFile(FILE* file)
{
    assert(file);
    fseek(file, 0, SEEK_END); // goto the end
    size_t length = ftell(file);
    fseek (file, 0, SEEK_SET); // back to the beginning
    char* str = malloc (length);
    if (str)
        fread (str, 1, length, file);
    return str;
}
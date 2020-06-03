#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char** argv)
{
    if(argc == 2) {
        FILE* file = fopen(argv[1], "r");
        if(!file) {
            printf("ERROR: couln't open file %s\n", argv[1]);
            return 1;
        }
        char* str = readStringFromFile(file);
        printf("This is your program:\n%s\n", str);
        free(str);
    }
    else {
        printf("ERROR:\n comp file.c\n");
    }
}
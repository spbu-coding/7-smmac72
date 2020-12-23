#ifndef MANAGE_STRINGS
#define MANAGE_STRINGS

#include <stdio.h>
#include <stdlib.h>
void freeArray(char **strings, int len, ERROR *LastError);
char **readFile(char *filename, int *stringAmount, ERROR *LastError);

#endif

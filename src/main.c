#include <stdio.h>
#include "sorting.h"
#include "manage_strings.h"

enum ERRORS
{
    STATUS_OK,
    ERR_ARGUMENT_NUM
} error_code;

int main(int argc, char **argv)
{
    char **strings;
    int stringAmount = 0;
    if (argc != 2)
    {
        fprintf(stdout,"Use %s <input file>.txt\n", argv[0]);
        return -1;
    }
    if (!(strings = readFile(argv[1], &stringAmount)))
    {
        return -1;
    }

    insertion(strings, stringAmount);
    for (int i = 0; i < stringAmount && i < 100; i++)
        fprintf(stdout, "%s", strings[i]);
    freeArray(strings, stringAmount);
    return 0;
}
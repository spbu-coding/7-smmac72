#include <stdio.h>
#include "sorting.h"
#include "manage_strings.h"

ERRORS LastError = STATUS_OK;

int checkError()
{
    switch(LastError)
    {
        case STATUS_OK:
            return 0;

        case ERR_ARGUMENT_NUM:
            printf("Two arguments are required.\n");
            return -1;

        case ERR_ALLOC:
            printf("Unable to allocate sufficient memory!\n");
            return -1;

        case ERR_OPEN_FILE:
            printf("Unable to locate and open the file :(\n");
            return -1;

        default:
            printf("Strange error! Contact the developer, please.\n");
            return -1;
    }
}

int main(int argc, char **argv)
{
    char **strings;
    int stringAmount = 0;
    if (argc != 2)
    {
        LastError = ERR_ARGUMENT_NUM;
        return checkError();
    }
    if (!(strings = readFile(argv[1], &stringAmount, &LastError)))
    {
        return checkError();
    }

    insertion(strings, stringAmount);
    for (int i = 0; i < stringAmount && i < 100; i++)
        fprintf(stdout, "%s", strings[i]);
    freeArray(strings, stringAmount);
    return 0;
}
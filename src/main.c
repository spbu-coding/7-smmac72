#include <stdio.h>
#include "sorting.h"
#include "manage_strings.h"

int main(int argc, char **argv)
{
    char **strings;
    int stringAmount = 0;
    if (argc != 2)
    {
        printf("Two arguments are required.\n");
        return -1;
    }
    if (!(strings = readFile(argv[1], &stringAmount, &LastError)))
        return -1;

    insertion(strings, stringAmount);
    for (int i = 0; i < stringAmount && i < 100; i++)
        fprintf(stdout, "%s", strings[i]);
    freeArray(strings, stringAmount);
    return 0;
}
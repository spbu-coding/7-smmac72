#include "sorting.h"
int cmp(const char* string1, const char* string2)
{
    return strcmp(string1, string2);
}

static void swap(char** a, char** b)
{
    char* tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion(char** strings, int stringAmount)
{
    for (size_t i = 0; i < stringAmount; i++)
    {
        for (size_t j = i; j > 0; j--)
        {
            if (cmp(strings[j - 1], strings[j]) <= 0)
                swap(&strings[j-1], &strings[j]);
        }
    }
}
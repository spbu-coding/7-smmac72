#include "manage_strings.h"

void freeArray(char **strings, int len)
{
    for (int i = 0; i < len; i++)
        free(strings[i]);
    free(strings);
}

char *removeSymbols(const char *buffer, int fileSize, int *stringAmount, int *len, ERROR *LastError)
{
    int chars = 0;
    char *buffer2 = calloc(fileSize + 2, sizeof(char));
    if (!buffer2)
    {
        LastError = ERR_ALLOC;
        return NULL;
    }
    int i = 0;
    while (chars < fileSize)
    {
        if (buffer[chars] != '.' && buffer[chars] != ',' && buffer[chars] != ';' && buffer[chars] != ':' && buffer[chars] != '!' && buffer[chars] != '?')
        {
            if (buffer[chars] == '\n')
                *stringAmount = *stringAmount + 1;
            buffer2[i] = buffer[chars];
            *len = *len + 1;
            chars++;
            i++;
        }
        else
            chars++;
        i++;
    }
    if (buffer2[i - 1] != '\n')
    {
        buffer2[i] = '\r';
        buffer2[i + 1] = '\n';
        *len = *len + 2;
        *stringAmount = *stringAmount + 1;
    }
    return buffer2;
}

char **newArray(const char *buffer2, int stringAmount, int len, ERROR *LastError)
{
    int chars = 0, stringLen = 0;
    char **array_of_strings = calloc(stringAmount, sizeof(char *));
    if (!array_of_strings)
    {
        LastError = ERR_ALLOC;
        return NULL;
    }
    for (int i = 0; i < stringAmount; i++)
    {
        array_of_strings[i] = calloc(1000, sizeof(char));
        if (!array_of_strings[i])
        {
            freeArray(array_of_strings, i);
            LastError = ERR_ALLOC;
            return NULL;
        }
        stringLen = 0;
        while (chars < len)
        {
            array_of_strings[i][stringLen] = buffer2[chars];
            stringLen++;
            if (buffer2[chars] == '\n')
            {
                chars++;
                break;
            }
            chars++;
        }
    }
    return array_of_strings;
}

int getFileSize(FILE *file)
{
    int fileSize;
    fseek(file,0, SEEK_END);
    fileSize = (int)ftell(file);
    fseek(file,0, SEEK_SET);
    return fileSize;
}

char **readFile(char *filename, int *stringAmount, ERRORS *LastError)
{
    FILE *file;
    if ((file = fopen(filename, "rb")) == NULL)
    {
        *LastError = ERR_OPEN_FILE;
        return NULL;
    }
    int fileSize = getFileSize(file);
    char *buffer = calloc(fileSize, sizeof(char));
    if (!buffer)
    {
        fclose(file);
        *LastError = ERR_ALLOC;
        return NULL;
    }
    fread(buffer, fileSize, sizeof(char), file);
    char *buffer2;
    int len = 0;
    if (!(buffer2 = removeSymbols(buffer, fileSize, stringAmount, &len, &LastError)))
    {
        fclose(file);
        free(buffer);
        *LastError = ERR_ALLOC;
        return NULL;
    }
    char **strings;
    if (!(strings = newArray(buffer2, *stringAmount, len, &LastError)))
    {
        fclose(file);
        free(buffer);
        free(buffer2);
        *LastError = ERR_ALLOC;
        return NULL;
    }
    free(buffer);
    free(buffer2);
    fclose(file);
    return strings;
}

#ifndef ERRORS
#define ERRORS

enum ERRORS
{
    STATUS_OK,
    ERR_ARGUMENT_NUM,
    ERR_ALLOC,
    ERR_OPEN_FILE
} error_code;

ERRORS LastError = STATUS_OK;

#endif

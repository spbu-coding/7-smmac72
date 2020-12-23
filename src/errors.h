#ifndef ERRORS
#define ERRORS

enum ERRORS
{
    STATUS_OK,
    ERR_ARGUMENT_NUM,
    ERR_ALLOC,
    ERR_OPEN_FILE
} error_code;

error_code LastError = STATUS_OK;

#endif

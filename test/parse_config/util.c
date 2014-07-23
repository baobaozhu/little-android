
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/*
 * add \n and '0' at the end of the data
*/
void *read_file(const char *file_path, unsigned *size)
{
    void *data = NULL;
    unsigned char *temp_buffer = NULL;
    unsigned file_size = 0;
    unsigned left_size = 0;
    size_t file_read = 0;
    int nRet = 0;

    FILE * pFile = fopen(file_path, "r");
    if (NULL==pFile) {
        goto exit;
    }

    nRet = fseek(pFile, 0, SEEK_END);
    if (0!=nRet) {
        goto exit;
    }

    file_size = (unsigned)ftell(pFile);
    if (0>=file_size) {
        goto exit;
    }

    nRet = fseek(pFile, 0, SEEK_SET);
    if (0!=nRet) {
        goto exit;
    }

    temp_buffer = malloc(file_size+2);
    if (NULL==temp_buffer) {
        goto exit;
    }

    temp_buffer[file_size+1] = 0;
    temp_buffer[file_size] = '\n';
    data = temp_buffer;
    left_size = file_size;
    while (0<left_size) {
        file_read = fread(temp_buffer, 1, left_size, pFile);
        if (0>=file_read) {
            free(data);
            data = NULL;
            break;
        }

        left_size -= file_read;
        temp_buffer += file_read;
    }

exit:
    if (NULL!=pFile) {
        fclose(pFile);
    }

    if (NULL!=data && NULL!=size) {
        *size = file_size;
    }

    return data;
}
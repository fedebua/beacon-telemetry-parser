#include <stdio.h>
#include <errno.h>
#include "parser.h"
#include "common.h"

long open_file(int argc, char* argv[], FILE** fp)
{
    // This function may have prints since the error management makes sense if reading from a file
    // Even though, the return values can be used in an upper layer
    // fp as argument for later closing it
    long file_size;

    // Check command-line arguments
    if (argc != 2) {
        debug("Usage: %s <binary_file>\n", argv[0]);
        return -EINVAL;
    }

    // Open the binary file
    *fp = fopen(argv[1], "rb");
    if (*fp == NULL) {
        debug("Error opening file");
        return -EACCES;
    }

    // Get file size in bytes
    if (fseek(*fp, 0, SEEK_END) != 0) {
        debug("Error seeking file end");
        fclose(*fp);
        return -EBADF;
    }

    file_size = ftell(*fp);
    if (file_size < 0) {
        debug("Error telling file size");
        fclose(*fp);
        return EBADF;
    }

    rewind(*fp);  // go back to beginning for later reads

    return file_size;
}
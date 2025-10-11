#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"

size_t read_telemetry(int argc, char* argv[], FILE** fp, beacon_telemetry_t* telemetry)
{
    // fp as argument for later closing it
    // This function may have prints since the error management makes sense if reading from a file
    // Even though, the return values can be used in an upper layer
    size_t bytesRead;

    // Check command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_file>\n", argv[0]);
        return -EINVAL;
    }

    // Open the binary file
    *fp = fopen(argv[1], "rb");
    if (*fp == NULL) {
        fprintf(stderr, "Error opening file");
        return -EACCES;
    }

    // Read 1 element of TELEMETRY_SIZE bytes
    bytesRead = fread(telemetry, 1, TELEMETRY_SIZE, *fp);
    if (bytesRead == 0) {
        fprintf(stderr, "No data read or file is empty.\n");
        fclose(*fp);        
        return -EBADF;
    }

    return bytesRead; // In case it is OK, return the amount of bytes read
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"

int main(int argc, char *argv[]) 
{
    FILE *fp;
    beacon_telemetry_t telemetry; // buffer to hold read bytes
    uint8_t* buffer = (uint8_t*) &telemetry; // buffer to show bytes
    size_t bytesRead = read_telemetry(argc, argv, &fp, &telemetry);

    if(bytesRead < 0)
        return EXIT_FAILURE; // messages managed inside

    if((bytesRead >= 0) && (bytesRead != TELEMETRY_SIZE))
    {
        fprintf(stderr, "%ld bytes were read from file instead of expected %ld\n", bytesRead, TELEMETRY_SIZE);
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Print bytes in hexadecimal
    for (size_t i = 0; i < bytesRead; i++)
        printf("%02X ", buffer[i]);
    printf("\n");

    fclose(fp);
    return EXIT_SUCCESS;
}
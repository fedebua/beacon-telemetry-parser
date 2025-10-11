#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "utils.h"
#include "common.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    long file_size, number_of_telemetries;
    ssize_t telemetries_read;
    int i;
    beacon_telemetry_t* telemetries;

    // Open file and get its size
    file_size = open_file(argc, argv, &fp);
    if(file_size < 0)
        return EXIT_FAILURE; // messages managed inside

    // Get the number of telemetries that fit in that file
    number_of_telemetries = file_size/TELEMETRY_SIZE;
    if(number_of_telemetries == 0)
    {
        debug("Number of telemetries is 0 which is invalid\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Allocate memory for those telemetries to avoid fixing the telemetry size
    telemetries = malloc(number_of_telemetries * sizeof(beacon_telemetry_t));
    if(!telemetries)
    {
        debug("Error allocating memory for telemetries\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    // Read all the telemetries
    telemetries_read = read_telemetries(fp, telemetries, number_of_telemetries);
    if(telemetries_read != number_of_telemetries)
    {
        free(telemetries);
        fclose(fp);
        return EXIT_FAILURE; // messages managed inside
    }

    for(i = 0; i < telemetries_read; i++)
        printf("%f ", get_thermal_CPU_C(&telemetries[i]));
    printf("\n");

    free(telemetries);
    fclose(fp);
    return EXIT_SUCCESS;
}
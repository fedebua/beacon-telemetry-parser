#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "common.h"

ssize_t read_telemetries(FILE* fp, beacon_telemetry_t* telemetry, size_t num_telemetries)
{
    // Read N element of TELEMETRY_SIZE bytes
    // This function may also print because it uses filesystem
    size_t telemetries_read = fread(telemetry, TELEMETRY_SIZE, num_telemetries, fp);
    if(telemetries_read != num_telemetries)
    {
        debug("Error reading telemetry. Returned %ld instead of expected %ld\n", telemetries_read, num_telemetries);
        telemetries_read = -EIO;
    }

    return telemetries_read; // In case it is OK, return the amount of telemetries read
}

double get_thermal_CPU_C(beacon_telemetry_t* telemetry)
{
    return (double)(BE16(telemetry->thermal.CPU_C))/CPU_C_CT_DIV;
}

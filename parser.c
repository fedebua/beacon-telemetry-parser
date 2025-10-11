#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "common.h"

static int compare_by_rtc(const void* a, const void* b) {
    // Convert al RTC measurements to little endian and compare them for the qsort
    const beacon_telemetry_t* ta = a;
    const beacon_telemetry_t* tb = b;
    if (BE32(ta->platform.rtc_s) < BE32(tb->platform.rtc_s)) return -1;
    if (BE32(ta->platform.rtc_s) > BE32(tb->platform.rtc_s)) return 1;
    return 0;
}

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

    // sort telemetries in the previously read array
    qsort(telemetry, num_telemetries, sizeof(beacon_telemetry_t), compare_by_rtc);

    return telemetries_read; // In case it is OK, return the amount of telemetries read
}

void load_values_array(double* values, double (*func_ptr)(beacon_telemetry_t*), beacon_telemetry_t* telemetry, long number_of_telemetries)
{
    int i;
    for(i = 0; i < number_of_telemetries; i++)
        values[i] = func_ptr(&telemetry[i]);
}

double get_thermal_CPU_C(beacon_telemetry_t* telemetry)
{
    int16_t raw = BE16(telemetry->thermal.CPU_C);
    return ((double)raw)/CPU_C_CT_DIV;
}

double get_aocs_sunvectorX(beacon_telemetry_t* telemetry)
{
    int16_t raw = BE16(telemetry->aocs.sunvectorX);
    return ((double)raw)/SUNVECTORX_CT_DIV;
}

double get_aocs_sunvectorY(beacon_telemetry_t* telemetry)
{
    int16_t raw = BE16(telemetry->aocs.sunvectorY);
    return ((double)raw)/SUNVECTORY_CT_DIV;
}

double get_aocs_sunvectorZ(beacon_telemetry_t* telemetry)
{
    int16_t raw = BE16(telemetry->aocs.sunvectorZ);
    return ((double)raw)/SUNVECTORZ_CT_DIV;
}

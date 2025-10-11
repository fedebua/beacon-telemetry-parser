#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "utils.h"
#include "common.h"

#define TELEMETRY_FILEPATH ("telemetry.csv")
#define SUN_VECTORX_TELEMETRY_NAME ("Sun Vector X")
#define SUN_VECTORY_TELEMETRY_NAME ("Sun Vector Y")
#define SUN_VECTORZ_TELEMETRY_NAME ("Sun Vector Z")
#define CPU_TEMPERATURE_TELEMETRY_NAME ("CPU temperature")

int main(int argc, char *argv[])
{
    FILE *fp;
    int ret;
    long file_size, number_of_telemetries;
    ssize_t telemetries_read;
    beacon_telemetry_t* telemetries;
    double* values;

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

    values = malloc(number_of_telemetries*sizeof(double));
    if(!values)
    {
        debug("Error allocating memory for values array\n");
        free(telemetries);
        fclose(fp);
        return EXIT_FAILURE; // messages managed inside
    }

    remove(TELEMETRY_FILEPATH); // Try to remove. Do not care if it fails

    // Load SUN VECTOR X values
    load_values_array(values, get_aocs_sunvectorX, telemetries, number_of_telemetries);
    ret = add_to_csv(TELEMETRY_FILEPATH, SUN_VECTORX_TELEMETRY_NAME, values, number_of_telemetries);
    if(ret) // Continue the program at this point, it will just fail writing
        debug("Error trying to write %s telemetry", SUN_VECTORX_TELEMETRY_NAME);

    // Load SUN VECTOR Y values
    load_values_array(values, get_aocs_sunvectorY, telemetries, number_of_telemetries);
    ret = add_to_csv(TELEMETRY_FILEPATH, SUN_VECTORY_TELEMETRY_NAME, values, number_of_telemetries);
    if(ret) // Continue the program at this point, it will just fail writing
        debug("Error trying to write %s telemetry", SUN_VECTORY_TELEMETRY_NAME);

    // Load SUN VECTOR Z values
    load_values_array(values, get_aocs_sunvectorZ, telemetries, number_of_telemetries);
    ret = add_to_csv(TELEMETRY_FILEPATH, SUN_VECTORZ_TELEMETRY_NAME, values, number_of_telemetries);
    if(ret) // Continue the program at this point, it will just fail writing
        debug("Error trying to write %s telemetry", SUN_VECTORZ_TELEMETRY_NAME);

    // Load CPU temperature values
    load_values_array(values, get_thermal_CPU_C, telemetries, number_of_telemetries);
    ret = add_to_csv(TELEMETRY_FILEPATH, CPU_TEMPERATURE_TELEMETRY_NAME, values, number_of_telemetries);
    if(ret) // Continue the program at this point, it will just fail writing
        debug("Error trying to write %s telemetry", CPU_TEMPERATURE_TELEMETRY_NAME);

    // Cleanup
    free(values);
    free(telemetries);
    fclose(fp);
    return EXIT_SUCCESS;
}
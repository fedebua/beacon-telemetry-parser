#ifndef TELEMETRY_PARSER_H
#define TELEMETRY_PARSER_H

#include <stdint.h>

// Indicate the compiler to pack structures in 1 bytes (to avoid empty offsets inside the full struct)
#pragma pack(push, 1)

typedef struct{
    uint16_t platform_id;
    uint32_t uptime_s; // uptime in seconds
    uint32_t rtc_s; // seconds since 00:00 1/1/1970 UTC
    uint8_t resetCount[3];
    uint8_t currentMode; // mode = value & 0x7F / computer = value & 0x80 (B=0, A=1)
    uint32_t lastBootReason;
}platform_telemetry_t;

typedef struct{
    uint16_t memory_id;
    uint32_t free; // heap free bytes
}memory_telemetry_t;

typedef struct{
    uint16_t cdh_id;
    uint32_t lastSeenSequenceNumber;
    uint8_t antennaDeployStatus;
}cdh_telemetry_t;

typedef enum{
    BATTERY_A_CT = 5237/1000,
    PCM_3V3_V_CT = 3988/1000,
    PCM_3V3_A_CT = 5237/1000,
    PCM_5V_V_CT = 5865/1000,
    PCM_5V_A_CT = 5237/1000,
}power_telemetry_constants_t;

typedef struct{
    uint16_t power_id;
    uint16_t low_voltage_counter;
    uint16_t nice_battery_mV;
    uint16_t raw_battery_mV;
    uint16_t battery_A;
    uint16_t pcm_3v3_V;
    uint16_t pcm_3v3_A;
    uint16_t pcm_5v_V;
    uint16_t pcm_5v_A;
}power_telemetry_t;

typedef enum{
    CPU_C_CT_DIV = 100,
    MIRROR_CELL_C_CT_DIV = 100,
}thermal_telemetry_constants_t;

typedef struct{
    uint16_t thermal_id;
    int16_t CPU_C;
    int16_t mirror_cell_C;
}thermal_telemetry_t;

typedef enum{
    SUNVECTORX_CT_DIV = 16384,
    SUNVECTORY_CT_DIV = 16384,
    SUNVECTORZ_CT_DIV = 16384,
    MAGNETOMETERX_MG_CT_DIV = 2,
    MAGNETOMETERY_MG_CT_DIV = 2,
    MAGNETOMETERZ_MG_CT_DIV = 2,
    GYROX_DPS_CT_DIV = 80,
    GYROY_DPS_CT_DIV = 80,
    GYROZ_DPS_CT_DIV = 80,
    TEMPERATURE_IMU_C_CT = (14/100),
    TEMPERATURE_IMU_C_OFF = 25,
    FINE_GYROX_DPS_CT = (256/6300)/65536,
    FINE_GYROY_DPS_CT = (256/6300)/65536,
    FINE_GYROZ_DPS_CT = (256/6300)/65536,
    WHEEL_1_RADSEC_CT = 3/10,
    WHEEL_2_RADSEC_CT = 3/10,
    WHEEL_3_RADSEC_CT = 3/10,
    WHEEL_4_RADSEC_CT = 3/10,

}aocs_telemetry_constants_t;

typedef struct{
    uint16_t aocs_id;
    uint32_t mode;
    int16_t sunvectorX;
    int16_t sunvectorY;
    int16_t sunvectorZ;
    int16_t magnetometerX_mg;
    int16_t magnetometerY_mg;
    int16_t magnetometerZ_mg;
    int16_t gyroX_dps;
    int16_t gyroY_dps;
    int16_t gyroZ_dps;
    int16_t temperature_IMU_C;
    int32_t fine_gyroX_dps;
    int32_t fine_gyroY_dps;
    int32_t fine_gyroZ_dps;
    int16_t wheel_1_radsec;
    int16_t wheel_2_radsec;
    int16_t wheel_3_radsec;
    int16_t wheel_4_radsec;
}aocs_telemetry_t;

typedef struct{
    uint16_t payload_id;
    uint16_t experimentsRun;
    uint16_t experimentsFailed;
    int16_t lastExperimentRun;
    uint8_t currentState;
}payload_telemetry_t;

typedef struct{
    uint8_t beacon_id[3];
    platform_telemetry_t platform;
    memory_telemetry_t memory;
    cdh_telemetry_t cdh;
    power_telemetry_t power;
    thermal_telemetry_t thermal;
    aocs_telemetry_t aocs;
    payload_telemetry_t telemetry;
}beacon_telemetry_t;

// Finish the struct package indication for the compiler
#pragma pack(pop)

#define TELEMETRY_SIZE (sizeof(beacon_telemetry_t))

size_t read_telemetry(int argc, char* argv[], FILE** fp, beacon_telemetry_t* telemetry);

#endif /* TELEMETRY_PARSER_H */
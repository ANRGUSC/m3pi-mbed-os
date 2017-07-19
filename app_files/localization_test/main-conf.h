/* Include this file to create project-specific macros. Try to keep their use
in the application code, not inside libraries. */

/* keep this port under 255 because the application code is not ready to adapt
the new uint16_t port number */


/* RSSI dump thread port number */
#define RSSI_DUMP_PORT              9000

#define GET_SET_RANGING_THR_PORT    9100

/* for ARREST, set follower's short hwaddr here */
#define ARREST_FOLLOWER_SHORT_HWADDR    "ec:e1"
#define ARREST_LEADER_SHORT_HWADDR      "ed:81"

#define RSSI_LOCALIZATION_CHAN   26

#define ARREST_LEADER_SOUNDRF_IPV6_ADDR   "fe80::212:4b00:433:ed81"

#define ARREST_LEADER_SOUNDRF_PORT  9200

#define ARREST_LEADER_SOUNDRF_ID    170

#define ARREST_FOLLOWER_RANGE_THR_PORT  9300

#define RANGE_REQ_FLAG      0x12
#define RANGE_RDY_FLAG      0x34
#define RANGE_GO_FLAG       0x56

#define DEFAULT_ULTRASOUND_THRESH   25

#define ONE_SENSOR_MODE       0x60 // 96
#define TWO_SENSOR_MODE       0x61 // 97
#define XOR_SENSOR_MODE       0x62 // 98
#define RANGE_DATA_LEN    5

/**
 * @brief Structure holding metrics measured by ultrasound ranging
 *
 * This structure is supposed to hold the Time Difference of Arrival
 * (TDoA), Orientation Differential (OD) between the TDoA of two sensors,
 * and any an error flag to indicate if a pin had missed a ping.
 *
 * It can be extended
 */
typedef struct __attribute__((packed)){
    uint16_t tdoa; //time difference of arrival
    uint16_t orient_diff; //orientation differential
    uint8_t error; //error message for if one sensor misses pings
} range_data_t;

/**
 * @brief Structure holding parameters for ultrasound ranging
 *
 * This structure is supposed to be used to send and interpret
 * range request packets between mbed and openmote
 *
 * It can be extended
 */
typedef struct __attribute__((packed)){
    uint16_t num_samples;
    uint8_t ranging_mode;
    // add more options in the future?
} range_params_t;


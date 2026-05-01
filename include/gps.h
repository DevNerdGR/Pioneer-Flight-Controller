#include <stdint.h>
#include <stdbool.h>

#ifndef GPS_H
#define GPS_H

#define DATA_BUF_SIZE_GPS 128

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

typedef struct {
    char syncByte;
    char identifier[2];
    char formatter[3];
    char dataBuf[DATA_BUF_SIZE_GPS];
    uint8_t checksum;

} GpsFrame;

/**
 * Initialises UART communication with GPS module
 */
void init_gps(void);

/**
 * Read frame stored in UART FIFO
 * \return `true` if frame successfully read, false otherwise  
 */
bool gps_read_frame(GpsFrame* frame);

/**
 * Pretty printing of a frame
 */
void gps_print_frame(GpsFrame* frame);

/**
 * Pretty printing of a frame
 */
void gps_print_gga_frame(GpsFrame* frame);

#endif
#include <stdint.h>

#ifndef PLOTTER_H
#define PLOTTER_H


/**
 * Takes in an array of int16 and sends them over serial to host device running SerialPlotter.
 */
void plotter_send_data_int(int16_t* buf, uint8_t size);

#endif
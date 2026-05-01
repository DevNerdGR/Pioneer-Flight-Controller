#include <stdint.h>
#include <stdio.h>
#include "plotter.h"

#define SERIAL_SYNC_BYTE_PLOTTER '>'

void plotter_send_data_int(int16_t* buf, uint8_t size) {
    printf("%c", SERIAL_SYNC_BYTE_PLOTTER);
    for (uint8_t i = 0; i < size; i++) {
        printf(",%04x", buf[i] & 0xFFFF);
    }
    printf("\n");
}

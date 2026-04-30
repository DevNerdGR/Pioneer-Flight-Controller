#include "gps.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

uint8_t calcChecksum(char* data) {
    uint8_t cs = data[0];
    uint8_t len = strlen(data);
    for (uint8_t i = 1; i < len; i++) {
        cs = cs ^ data[i];
    }
    return cs;
}

void init_gps() {
    uart_init(UART_ID_GPS, BAUD_RATE_GPS);
    gpio_set_function(UART_TX_PIN_GPS, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN_GPS, GPIO_FUNC_UART);
}

bool gps_read_frame(GpsFrame* f) {
    do {
        if (!uart_is_readable_within_us(UART_ID_GPS, TIMEOUT_GPS)) return false;
        f->syncByte = uart_getc(UART_ID_GPS);
    } while (f->syncByte != SERIAL_SYNC_BYTE_GPS);

    for (uint8_t i = 0; i < 2; i++) {
        if (!uart_is_readable_within_us(UART_ID_GPS, TIMEOUT_GPS)) return false;
        f->identifier[i] = uart_getc(UART_ID_GPS);
    }

    for (uint8_t i = 0; i < 3; i++) {
        if (!uart_is_readable_within_us(UART_ID_GPS, TIMEOUT_GPS)) return false;
        f->formatter[i] = uart_getc(UART_ID_GPS);
    }

    uint8_t i = UINT8_MAX;
    do {
        i++;
        if (i >= DATA_BUF_SIZE_GPS || !uart_is_readable_within_us(UART_ID_GPS, TIMEOUT_GPS)) return false;
        f->dataBuf[i] = uart_getc(UART_ID_GPS);
    } while (f->dataBuf[i] != '*');
    f->dataBuf[i] = '\0';

    char buf[3];
    for (uint8_t i = 0; i < 2; i++) {
        if (!uart_is_readable_within_us(UART_ID_GPS, TIMEOUT_GPS)) return false;
        buf[i] = uart_getc(UART_ID_GPS);
    }
    buf[2] = '\0';
    f->checksum = (uint8_t) strtoul(buf, NULL, 16);

    
    uint8_t calculatedChecksum = calcChecksum(f->identifier);
    return true;//(calculatedChecksum == f->checksum);
}

void gps_print_frame(GpsFrame* frame) {
    printf(&(frame->syncByte));
    printf("\tChecksum: 0x%x02\n", frame->checksum);
}

void gps_print_gga_frame(GpsFrame* frame) {
    if (strncmp(frame->formatter, "GGA", 3) == 0) {
        printf(&(frame->syncByte));
        printf("\tChecksum: 0x%x02\n", frame->checksum);
    }
}

#include "rx.h"
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define BAUD_RATE 420000
#define UART_ID uart1
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define TIMEOUT 10

#define SERIAL_SYNC_BYTE 0xC8

#define MAX(a,b) ((a) > (b) ? (a) : (b))


void init_radio_rx() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

bool read_frame(Frame* f) {
    do {
        if (!uart_is_readable_within_us(UART_ID, TIMEOUT)) return false;
        f->syncByte = uart_getc(UART_ID);
    } while (f->syncByte != SERIAL_SYNC_BYTE);
    
    if (!uart_is_readable_within_us(UART_ID, TIMEOUT)) return false;
    f->frameLen = MAX(1, uart_getc(UART_ID));

    if (!uart_is_readable_within_us(UART_ID, TIMEOUT)) return false;
    f->type = uart_getc(UART_ID);

    for (uint8_t i=0; i < f->frameLen; i++) {
        if (!uart_is_readable_within_us(UART_ID, TIMEOUT)) return false;
        f->payload[i] = uart_getc(UART_ID);
    }
    return true;
}

void print_frame(Frame* f) {
    printf("Sync byte:\t%02x\n", f->syncByte);
    printf("Frame len:\t%02x\n", f->frameLen);
    printf("Type:\t%02x\n", f->type);
    printf("Payload:\t");
    for (uint8_t i = 0; i < f->frameLen - 1; i++) {
        printf("%02x ", f->payload[i]);
    }
    printf("\nCRC:\t%02x\n\n", f->payload[f->frameLen - 1]);
}



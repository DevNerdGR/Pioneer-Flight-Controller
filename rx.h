#include <stdint.h>
#include <stdbool.h>

#ifndef RX_H
#define RX_H

#define BAUD_RATE 420000
#define UART_ID uart1
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define TIMEOUT 10
#define SERIAL_SYNC_BYTE 0xC8

#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct {
    uint8_t syncByte;
    uint8_t frameLen;
    uint8_t type;
    uint8_t payload[61];
} Frame;

/**
 * Initialises UART communication with ELRS receiver module
 */
void init_radio_rx(void);

/**
 * Read frame stored in UART FIFO
 * \return `true` if frame successfully read, false otherwise  
 */
bool read_frame(Frame* frame);

/**
 * Pretty printing of a frame
 */
void print_frame(Frame* frame);


#endif
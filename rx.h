#include <stdint.h>
#include <stdbool.h>

#ifndef RX_H
#define RX_H

#define BAUD_RATE_RX 420000
#define UART_ID_RX uart1
#define UART_TX_PIN_RX 4
#define UART_RX_PIN_RX 5
#define TIMEOUT_RX 10
#define SERIAL_SYNC_BYTE_RX 0xC8

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

typedef struct {
    uint8_t syncByte;
    uint8_t frameLen;
    uint8_t type;
    uint8_t payload[61];
} RxFrame;

/**
 * Initialises UART communication with ELRS receiver module
 */
void rx_init_radio(void);

/**
 * Read frame stored in UART FIFO
 * \return `true` if frame successfully read, false otherwise  
 */
bool rx_read_frame(RxFrame* frame);

/**
 * Pretty printing of a frame
 */
void rx_print_frame(RxFrame* frame);


#endif
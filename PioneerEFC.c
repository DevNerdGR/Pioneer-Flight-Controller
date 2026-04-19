#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"

#define BAUD_RATE 420000
#define UART_ID uart1
#define UART_TX_PIN 4
#define UART_RX_PIN 5

void init_elrs_rx() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void init() {
    stdio_init_all();
    init_elrs_rx();
}


int main() {
    init();   

    while (true) {
        if (uart_is_readable(UART_ID)) {
            uint8_t data = uart_getc(UART_ID);
            printf("%02x", data);
        }
    }

}

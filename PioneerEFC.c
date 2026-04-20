#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "rx.h"

void init() {
    stdio_init_all();
    init_radio_rx();
}

int main() {
    init();

    while (true) {
        Frame f;
        if (read_frame(&f)) {
            print_frame(&f);
        }

        sleep_ms(50);
    }
}
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "rx.h"
#include "command.h"

void init() {
    stdio_init_all();
    init_radio_rx();
    cyw43_arch_init();
}

int main() {
    init();

    while (true) {
        Frame f;
        CommandPacket cp;
        if (read_frame(&f) && parse_command_frame(&f, &cp)) {
            //print_command_packet(&cp);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, cp.channel_05 > COMMAND_HIGH_THRESH);
        }
        sleep_ms(10);
    }
}
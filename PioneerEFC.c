#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "rx.h"
#include "command.h"
#include "gps.h"
#include "plotter.h"


void init() {
    stdio_init_all();
    rx_init_radio();
    init_gps();
    cyw43_arch_init();
}

int main() {

    init();



    while (true) {
        RxFrame f;
        CommandPacket cp;
        if (rx_read_frame(&f) && parse_command_frame(&f, &cp)) {
            //print_command_packet(&cp);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, cp.channel_03 > COMMAND_HIGH_THRESH);
        }

        GpsFrame g;        
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, gps_read_frame(&g));


        sleep_ms(10);
    }
}
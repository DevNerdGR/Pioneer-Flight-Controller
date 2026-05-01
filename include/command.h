#include "rx.h"
#include <stdint.h>

#define TICKS_TO_US(x) ((x - 992) * 5 / 8 + 1500)
#define US_TO_TICKS(x) ((x - 1500) * 8 / 5 + 992)

#ifndef COMMAND_H
#define COMMAND_H

#define COMMAND_MIN 60
#define COMMAND_NEUTRAL 500 + COMMAND_MIN
#define COMMAND_MAX 1000 + COMMAND_MIN
#define COMMAND_HIGH_THRESH 850 + COMMAND_MIN
#define COMMAND_LOW_THRESH 150 + COMMAND_MIN



// Commands range from 0 to 1000
typedef struct {
    uint16_t channel_01;
    uint16_t channel_02;
    uint16_t channel_03;
    uint16_t channel_04;
    uint16_t channel_05;
    uint16_t channel_06;
    uint16_t channel_07;
    uint16_t channel_08;
    uint16_t channel_09;
    uint16_t channel_10;
    uint16_t channel_11;
    uint16_t channel_12;
    uint16_t channel_13;
    uint16_t channel_14;
    uint16_t channel_15;
    uint16_t channel_16;
} CommandPacket;

/**
 * Parses a RxFrame from the RX to channels format (CommandPacket)
 * \return `true` if successful, `false` otherwise
 */
bool parse_command_frame(RxFrame* f, CommandPacket* cp);

/**
 * Pretty printing of a command packet.
 */
void print_command_packet(CommandPacket* cp);
#endif
#include "rx.h"

#define TICKS_TO_US(x) ((x - 992) * 5 / 8 + 1500)
#define US_TO_TICKS(x) ((x - 1500) * 8 / 5 + 992)

#ifndef COMMAND_H
#define COMMAND_H

#define PACKET_TYPE_RC_CHANNEL 0x16

#define COMMAND_NEUTRAL 50
#define COMMAND_MAX 100
#define COMMAND_MIN 0
#define COMMAND_HIGH_THRESH 85
#define COMMAND_LOW_THRESH 15

#define NORM_OFFSET 10
#define NORM_SCALE  100 / (1800 - 170) // 1000 / (max - min)

// Commands range from 0 to 1000
typedef struct {
    unsigned int channel_01: 11;
    unsigned int channel_02: 11;
    unsigned int channel_03: 11;
    unsigned int channel_04: 11;
    unsigned int channel_05: 11;
    unsigned int channel_06: 11;
    unsigned int channel_07: 11;
    unsigned int channel_08: 11;
    unsigned int channel_09: 11;
    unsigned int channel_10: 11;
    unsigned int channel_11: 11;
    unsigned int channel_12: 11;
    unsigned int channel_13: 11;
    unsigned int channel_14: 11;
    unsigned int channel_15: 11;
    unsigned int channel_16: 11;
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
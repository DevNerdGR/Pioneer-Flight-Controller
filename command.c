#include "command.h"
#include "pico/stdlib.h"
#include <stdio.h>

bool parse_command_frame(Frame* f, CommandPacket* cp) {
    if (f->type != PACKET_TYPE_RC_CHANNEL) return false;
    /**
     * Bit mask:
     * 1: 0x1
     * 2: 0x3
     * 3: 0x7
     * 4: 0xF
     * 5: 0x1F
     * 6: 0x3F
     * 7: 0x7F
     * 8: 0xFF
     */
    cp->channel_01 = ((f->payload[0] | ((f->payload[1] & 0x7) << 8))) * NORM_SCALE - NORM_OFFSET;
    cp->channel_02 = ((f->payload[1] >> 3) | ((f->payload[2] & 0x3F) << 5)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_03 = ((f->payload[2] >> 6) | ((f->payload[3] & 0xFF) << 2) | ((f->payload[4] & 0x1) << 10)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_04 = ((f->payload[4] >> 1) | ((f->payload[5] & 0xF) << 7)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_05 = ((f->payload[5] >> 4) | ((f->payload[6] & 0x7F) << 4)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_06 = ((f->payload[6] >> 7) | ((f->payload[7] & 0xFF) << 1) | ((f->payload[8] & 0x3) << 9)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_07 = ((f->payload[8] >> 2) | ((f->payload[9] & 0x1F) << 6)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_08 = ((f->payload[9] >> 5) | ((f->payload[10] & 0xFF) << 3)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_09 = ((f->payload[11]) | ((f->payload[12] & 0x7) << 8)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_10 = ((f->payload[12] >> 3) | ((f->payload[13] & 0x3F) << 5)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_11 = ((f->payload[13] >> 6) | ((f->payload[14] & 0xFF) << 2) | ((f->payload[15] & 0x1) << 10)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_12 = ((f->payload[15] >> 1) | ((f->payload[16] & 0xF) << 7)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_13 = ((f->payload[16] >> 4) | ((f->payload[17] & 0x7F) << 4)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_14 = ((f->payload[17] >> 7) | ((f->payload[18] & 0xFF) << 1) | ((f->payload[19] & 0x3) << 9)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_15 = ((f->payload[19] >> 2) | ((f->payload[20] & 0x1F) << 6)) * NORM_SCALE - NORM_OFFSET;
    cp->channel_16 = ((f->payload[20] >> 5) | ((f->payload[21] & 0xFF) << 3)) * NORM_SCALE - NORM_OFFSET;
    return true;
}

void print_command_packet(CommandPacket* cp) {
    printf("Command packet\n");
    printf("Channel\t01\t02\t03\t04\t05\t06\t07\t08\t09\t10\t11\t12\t13\t14\t15\t16\n");
    printf("Value\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\t%02d\n", 
        cp->channel_01, cp->channel_02, cp->channel_03, cp->channel_04, cp->channel_05, cp->channel_06, cp->channel_07, cp->channel_08, 
        cp->channel_09, cp->channel_10, cp->channel_11, cp->channel_12, cp->channel_13, cp->channel_14, cp->channel_15, cp->channel_16);
}
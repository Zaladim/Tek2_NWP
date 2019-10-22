/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** print_opt
*/

#include "arpspoof.h"

int print_broadcast(data_t data)
{
    unsigned char *targ_mac = convert_mac("ff:ff:ff:ff:ff:ff");
    char *frame = create_arp_packet(data, ARPOP_REQUEST, targ_mac);

    for (size_t i = 0; i < HDR_LEN - 1; i++)
        printf("%02x ", (unsigned char) frame[i]);
    printf("%02x\n", (unsigned char) frame[HDR_LEN - 1]);
    free(frame);
    free(targ_mac);
    return 1;
}

int print_spoof(data_t data)
{
    unsigned char *targ_mac = convert_mac(data.mac);
    char *frame = create_arp_packet(data, ARPOP_REPLY, targ_mac);

    for (size_t i = 0; i < HDR_LEN - 1; i++)
        printf("%02x ", (unsigned char) frame[i]);
    printf("%02x\n", (unsigned char) frame[HDR_LEN - 1]);
    free(frame);
    free(targ_mac);
    return 1;
}
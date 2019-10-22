/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** arp_packet
*/

#include "arpspoof.h"

static eth_t *create_ether_hdr(arp_t *arp)
{
    eth_t *eth = malloc(ETH_LEN);

    if (!eth)
        exit(FAILURE);
    memcpy(&eth->h_dest, arp->target_mac, 6 * sizeof(unsigned char));
    memcpy(&eth->h_source, &arp->sender_mac, 6 * sizeof(unsigned char));
    eth->h_proto = htons(ETH_P_ARP);
    return eth;
}

static void fill_arp(arp_t *arp, char *sender_ip, char *targ_ip)
{
    unsigned int addr = converted_ip(sender_ip);

    memcpy(&arp->sender_ip, &addr, 4 * sizeof(unsigned char));
    addr = converted_ip(targ_ip);
    memcpy(arp->target_ip, &addr, 4 * sizeof(unsigned char));
}

static arp_t *create_arp_hdr(data_t data, int type_packet, \
unsigned char *targ_mac)
{
    unsigned char *own_mac = get_mac_from_iface(data.iface);
    arp_t *arp = malloc(sizeof(arp_t));

    if (!arp)
        exit(FAILURE);
    arp->hard_type = htons(ARPHRD_ETHER);
    arp->proto_type = htons(ETH_P_IP);
    arp->hard_size = 6;
    arp->proto_size = 4;
    arp->op_code = htons(type_packet);
    memcpy(&arp->sender_mac, own_mac, 6 * sizeof(unsigned char));
    if (type_packet == 1)
        memset(&arp->target_mac, 255, 6 * sizeof(unsigned char));
    else
        memcpy(&arp->target_mac, targ_mac, 6 * sizeof(unsigned char));
    free(own_mac);
    return arp;
}

void *create_arp_packet(data_t data, int type_packet, unsigned char *targ_mac)
{
    eth_t *eth = NULL;
    arp_t *arp = NULL;
    char *frame = malloc(HDR_LEN * sizeof(char));

    if (!frame)
        exit(FAILURE);
    arp = create_arp_hdr(data, type_packet, targ_mac);
    fill_arp(arp, data.source_ip, data.dest_ip);
    eth = create_ether_hdr(arp);
    memset(frame, 0, HDR_LEN);
    memcpy(frame, eth, ETH_LEN);
    memcpy(frame + ETH_LEN, arp, ARP_LEN);
    free(eth);
    free(arp);
    return frame;
}
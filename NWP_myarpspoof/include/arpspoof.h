/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** arpspoof
*/

#ifndef ARPSPOOF_H_
#define ARPSPOOF_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <net/if.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#define FAILURE 84

typedef struct arp {
    unsigned short int hard_type;
    unsigned short int proto_type;
    unsigned char hard_size;
    unsigned char proto_size;
    unsigned short int op_code;
    unsigned char sender_mac[6];
    unsigned char sender_ip[4];
    unsigned char target_mac[6];
    unsigned char target_ip[4];
} arp_t;

typedef struct ethhdr eth_t;

#define ARP_LEN sizeof(arp_t)
#define ETH_LEN sizeof(eth_t)
#define HDR_LEN ETH_LEN + ARP_LEN

typedef struct data {
    char *source_ip;
    char *dest_ip;
    char *iface;
    int p_broadcast;
    int p_spoof;
    char *mac;
} data_t;

// Common
void display_error(const char *msg);
int parser(int ac, char **av, data_t *data);
int lexer(data_t data);

// Create ARP packet
void *create_arp_packet(data_t data, int type_packet, unsigned char *targ_mac);

// Spoofing
int send_packet(data_t data, int fd, char *frame);
unsigned char *recv_packet(int fd);
int send_spoofed_packet(data_t data, int fd, char *frame);

// Utils
unsigned char *get_mac_from_iface(char *interface);
char *get_own_ip(char *interface);
unsigned int converted_ip(char *ip);
unsigned char *convert_mac(char *mac);

// Additionnal params
int print_broadcast(data_t data);
int print_spoof(data_t data);

#endif /* !ARPSPOOF_H_ */

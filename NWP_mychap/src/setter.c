/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Setter
*/

#include "mychap.h"

void set_buffer(char *buffer, hdr_t *hdr, char *msg, int len)
{
    memset(buffer, 0, sizeof(iphdr_t) + sizeof(udphdr_t) + (len + 1));
    memcpy(buffer, (void *) hdr->ip, sizeof(iphdr_t));
    memcpy(buffer + sizeof(iphdr_t), (void *) hdr->udp, sizeof(udphdr_t));
    memcpy(buffer + sizeof(iphdr_t) + sizeof(udphdr_t), msg, len);
}

void set_addr(addr_t *addr, args_t *args)
{
    addr->dest.sin_family = AF_INET;
    addr->dest.sin_port = htons(args->port);
    addr->dest.sin_addr.s_addr = inet_addr(args->target);
    addr->src.sin_family = AF_INET;
    addr->src.sin_port = htons(4242);
    addr->src.sin_addr.s_addr = inet_addr("127.0.0.1");
}
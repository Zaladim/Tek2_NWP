/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Header creation
*/

#include "mychap.h"


int create_header(hdr_t *hdr, args_t *args, int len)
{
    hdr->ip = malloc(sizeof(struct iphdr));
    hdr->udp = malloc(sizeof(struct udphdr));
    if (!(hdr->ip) || !(hdr->udp))
        return (dprintf(2, "Malloc : %s\n", strerror(errno)), EXIT_ERROR);
    hdr->ip->ihl = 5;
    hdr->ip->version = 4;
    hdr->ip->tos = 4;
    hdr->ip->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + len + 1;
    hdr->ip->id = 0;
    hdr->ip->ttl = 255;
    hdr->ip->frag_off = 0;
    hdr->ip->protocol = IPPROTO_UDP;
    hdr->ip->check = 0;
    hdr->ip->saddr = inet_addr("127.0.0.1");
    hdr->ip->daddr = inet_addr(args->target);
    hdr->udp->source = htons(4242);
    hdr->udp->dest = htons(args->port);
    hdr->udp->len = htons(sizeof(struct udphdr) + len + 1);
    hdr->udp->check = 0;
}
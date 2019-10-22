/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Reception
*/

#include "mychap.h"

static void print_secret(char *secret)
{
    if (strcmp(secret, "KO") == 0)
        printf("KO\n");
    else
        printf("Secret: '%s'\n", secret);
}

static int check_server(args_t *args, void *buff)
{
    iphdr_t *new_ip = buff;
    udphdr_t *new_udp = buff + sizeof(iphdr_t);

    if ((unsigned int)new_ip->saddr == (unsigned int)inet_addr(args->target) \
    && (uint16_t) new_udp->source == htons(args->port)) {
        if (((uint16_t)new_udp->dest) == (uint16_t)htons(4242)) {
            return 1;
        }
    }
    return 0;
}

static int reception_secret(int fd, addr_t *addr, hdr_t *hdr, args_t *args)
{
    char msg_recu[4096] = {0};
    socklen_t len_sock = sizeof(addr->src);
    int len;

    while (1) {
        if (recvfrom(fd, msg_recu, 4096, 0, \
            (struct sockaddr *) &(addr->src), &len_sock) < 0)
            return (dprintf(2, "Recvfrom : %s\n", strerror(errno)), EXIT_ERROR);
        len = strlen(sizeof(iphdr_t) + sizeof(udphdr_t) + msg_recu);
        if (check_server(args, msg_recu) == 1) {
            print_secret(sizeof(iphdr_t) + sizeof(udphdr_t) + msg_recu);
            return EXIT_SUCCESS;
        } else {
            memset(sizeof(iphdr_t) + sizeof(udphdr_t) + msg_recu, 0, len);
        }
    }
}

static int do_sendto(int fd, char *buffer, int len, addr_t *addr)
{
    if (sendto(fd, buffer, sizeof(iphdr_t) + sizeof(udphdr_t) + \
        (len + 1) , 0, (struct sockaddr *) &(addr->dest), \
        sizeof(addr->dest)) < 0)
        return (dprintf(2, "Sendto : %s\n", strerror(errno)), \
        EXIT_ERROR);
    return EXIT_SUCCESS;
}

int reception(int fd, addr_t *addr, hdr_t *hdr, args_t *args)
{
    char msg_recu[4096] = {0};
    char *buffer;
    char *buffer2;
    socklen_t len_sock = sizeof(addr->src);
    int len;

    while (1) {
        if (recvfrom(fd, msg_recu, 4096, 0, \
            (struct sockaddr *) &(addr->src), &len_sock) < 0)
            return (dprintf(2, "Recvfrom : %s\n", strerror(errno)), EXIT_ERROR);
        if (check_server(args, msg_recu) == 1) {
            buffer = hash((msg_recu + sizeof(iphdr_t) + sizeof(udphdr_t)), \
            args->password, strlen(args->password));
            len = strlen(buffer);
            buffer2 = malloc(sizeof(iphdr_t) + sizeof(udphdr_t) + (len + 1));
            create_header(hdr, args, len);
            set_buffer(buffer2, hdr, buffer, len);
            return (do_sendto(fd, buffer2, len, addr) == EXIT_SUCCESS \
            ? reception_secret(fd, addr, hdr, args) : EXIT_ERROR);
        }
    }
}
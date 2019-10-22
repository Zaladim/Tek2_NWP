/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Main
*/

#include "mychap.h"

static int close_client(hdr_t *hdr, addr_t *addr, args_t *args, char *buffer)
{
    free(hdr);
    free(args);
    free(addr);
    free(buffer);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    args_t *args = parser(argc, argv);
    hdr_t *hdr = malloc(sizeof(hdr_t));
    char *buffer = malloc(sizeof(iphdr_t) + sizeof(udphdr_t) + (LEN_HELLO + 1));
    int opt = 1;
    int fd = create_socket(opt);
    addr_t *addr = malloc(sizeof(addr_t));

    if (!hdr || !buffer || !addr)
        return (dprintf(2, "Malloc : %s\n", strerror(errno)), EXIT_ERROR);
    create_header(hdr, args, LEN_HELLO);
    set_buffer(buffer, hdr, HELLO, LEN_HELLO);
    set_addr(addr, args);
    if (sendto(fd, buffer, hdr->ip->tot_len, 0, \
        (struct sockaddr *) &(addr->dest), sizeof(addr->dest)) < 0)
        return (dprintf(1, "No such hostname: '%s'\n", args->target), \
        EXIT_ERROR);
    reception(fd, addr, hdr, args);
    close(fd);
    return close_client(hdr, addr, args, buffer);
}
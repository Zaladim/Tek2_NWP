/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Socket
*/

#include "mychap.h"

int create_socket(int opt)
{
    int fd;

    if ((fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0)
        return (dprintf(2, "Socket : %s\n", strerror(errno)), EXIT_ERROR);
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt)))
    return (dprintf(2, "setsockopt : %s\n", strerror(errno)), EXIT_ERROR);
    return fd;
}
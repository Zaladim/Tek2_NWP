/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** dele
*/

#include "server.h"

void dele(server_t *server, char *buffer)
{
    if (remove(buffer) == 0)
        dprintf(server->sock, "250 File succefully removed.\n");
    else
        dprintf(server->sock, "550 File not removed.\n");
}
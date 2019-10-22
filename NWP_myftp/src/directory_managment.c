/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** directory_managment
*/

#include "server.h"

void cwd(server_t *server, char *buffer)
{
    if (chdir(buffer) < 0)
        dprintf(server->sock, "550 Failed to change directory\n");
    else
        dprintf(server->sock, "250 Change directory.\n");
}

void cdup(server_t *server)
{
    if (chdir("../") < 0)
        dprintf(server->sock, "550 Failed to change directory\n");
    else
        dprintf(server->sock, "200 Directory changed to parent.\n");
}

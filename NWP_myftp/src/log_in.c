/*
** EPITECH PROJECT, 2019
** MYFTP
** File description:
** Log in
*/

#include "server.h"

int user(server_t *server, char *buffer)
{
    if (server->users[server->num_client]->name != 0) {
        return dprintf(server->sock, "230 User already logged in.\n", \
        EXIT_ERROR);
    }
    if (!strcmp(buffer, "Anonymous")) {
        server->users[server->num_client]->name = 1;
        dprintf(server->sock, "331 Username okay, enter password.\n");
        return EXIT_SUCCESS;
    } else {
        dprintf(server->sock, "331 This username doesn't exist.\n");
        return EXIT_ERROR;
    }
}

int pass(server_t *server, char *buffer)
{
    if (server->users[server->num_client]->pass != 0) {
        return dprintf(server->sock, "230 User already logged in.\n", \
        EXIT_ERROR);
    }
    if (server->users[server->num_client]->name != 0 && !strcmp(buffer, "")) {
        server->users[server->num_client]->pass = 1;
        dprintf(server->sock, "230 User logged in, proceed.\n");
        return EXIT_SUCCESS;
    } else {
        dprintf(server->sock, "530 Wrong password, \
        authentification failed.\n");
        return EXIT_ERROR;
    }
}
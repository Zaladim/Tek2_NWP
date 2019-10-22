/*
** EPITECH PROJECT, 2019
** MYFTP
** File description:
** Client connection
*/

#include "server.h"

static void set_client(server_t *server, user_t *client)
{
    for (int i = 0; i < NB_USER; i++) {
        if (server->users[i] == NULL || server->users[i]->fd == -1) {
            server->users[i] = client;
            break;
        }
    }
}

int client_connect(server_t *server, set_t *set)
{
    user_t *client = malloc(sizeof(user_t));

    if (!client)
        return (dprintf(2, "Malloc failed\n"), EXIT_ERROR);
    if ((client->fd = accept(server->serv.fd, NULL, NULL)) < 0)
        return (dprintf(2, "Accept failed\n"), EXIT_ERROR);
    FD_SET(client->fd, &(set->all_fd));
    client->name = 0;
    client->pass = 0;
    client->data_fd = -1;
    client->data_server_fd.fd = -1;
    set_client(server, client);
    return (dprintf(client->fd, "220 Welcome.\n"), EXIT_SUCCESS);
}
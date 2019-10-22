/*
** EPITECH PROJECT, 2019
** MYFTP
** File description:
** Server execution
*/

#include "server.h"

static int handle_socket(set_t *set, server_t *server)
{
    if (FD_ISSET(server->sock, &(set->cur_fd))) {
        if (server->sock == server->serv.fd) {
            return client_connect(server, set);
        } else {
            return detect_command(set, server);
        }
    }
}

static void find_num_client(server_t *server)
{
    for (int i = 0; i < NB_USER; i ++) {
        if (server->users[i] && server->sock == server->users[i]->fd) {
            server->num_client = i;
            break;
        }
    }
}

static int run_loop(set_t set, server_t *server)
{
    while (1) {
        set.cur_fd = set.all_fd;
        if (select(FD_SETSIZE, &(set.cur_fd), NULL, NULL, NULL) < 0)
            return (dprintf(2, "Select failed\n"), EXIT_ERROR);
        for (int i = 0; i < FD_SETSIZE; i++) {
            server->sock = i;
            find_num_client(server);
            handle_socket(&set, server);
            server->num_client = 0;
            server->sock = -1;
        }
    }
    return EXIT_SUCCESS;
}

int srv_run(server_t *server)
{
    set_t set;
    server->users = malloc(sizeof(user_t *) * (NB_USER + 1));

    if (server->users == NULL)
        return (dprintf(2, "Malloc failed\n"), EXIT_ERROR);
    for (int i = 0; i <= NB_USER; i++) {
        server->users[i] = NULL;
    }
    FD_ZERO(&set.all_fd);
    FD_SET(server->serv.fd, &(set.all_fd));
    return run_loop(set, server);
}
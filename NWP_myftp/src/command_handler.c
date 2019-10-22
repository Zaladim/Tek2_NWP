/*
** EPITECH PROJECT, 2019
** MY_FTP
** File description:
** Command handler
*/

#include "server.h"

static int check_log_in(server_t *server)
{
    if (server->users[server->num_client]->name == NULL)
        return (dprintf(server->sock, "530 User not connected.\n"), EXIT_ERROR);
    if (server->users[server->num_client]->pass == NULL)
        return (dprintf(server->sock, "530 User not connected (missing \
        password).\n"), EXIT_ERROR);
    return EXIT_SUCCESS;
}

int detect_command(set_t *set, server_t *server)
{
    char buffer[1024] = {0};
    int n;
    if ((n = read(server->sock, buffer, 1024)) != 0) {
        if (buffer[n - 1] == '\n')
            buffer[n - 1] = 0;
        if (buffer[n - 2] == '\r')
            buffer[n - 2] = 0;
        if (!command_base(server, set, buffer)) {
            return EXIT_SUCCESS;
        } else if (!check_log_in(server))
            commands(server, buffer);
    } else {
        close_socket(set, server);
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}
/*
** EPITECH PROJECT, 2019
** MYFTP
** File description:
** Commands
*/

#include "server.h"

static int commands_3(server_t *server, char *buffer)
{
    if (!strncmp(buffer, "RETR", 4)) {
        retr(server, buffer + 5);
        return EXIT_SUCCESS;
    }
    if (!strncmp(buffer, "STOR", 4)) {
        stor(server, buffer + 5);
        return EXIT_SUCCESS;
    }
    if (!strncmp(buffer, "LIST", 4)) {
        list(server);
        return EXIT_SUCCESS;
    }
    return (dprintf(server->sock, "500 Unknown command.\n"), EXIT_ERROR);
}

static int commands_2(server_t *server, char *buffer)
{
    if (!strcmp(buffer, "PASV")) {
        passive(server);
        return EXIT_SUCCESS;
    }
    if (!strcmp(buffer, "PORT")) {
        active(server, buffer + 5);
        return EXIT_SUCCESS;
    }
    if (!strcmp(buffer, "HELP")) {
        help(server);
        return EXIT_SUCCESS;
    }
    if (!strcmp(buffer, "NOOP")) {
        dprintf(server->sock, "200 Do nothing.\n");
        return EXIT_SUCCESS;
    }
    return (commands_3(server, buffer));
}

int commands(server_t *server, char *buffer)
{
    if (!strncmp(buffer, "CWD", 3)) {
        cwd(server, buffer + 4);
        return EXIT_SUCCESS;
    }
    if (!strcmp(buffer, "CDUP")) {
        cdup(server);
        return EXIT_SUCCESS;
    }
    if (!strncmp(buffer, "DELE", 4)) {
        dele(server, buffer + 5);
        return EXIT_SUCCESS;
    }
    if (!strcmp(buffer, "PWD")) {
        pwd(server);
        return EXIT_SUCCESS;
    }
    return (commands_2(server, buffer));
}

int command_base(server_t *server, set_t *set, char *buffer)
{
    if (!strcmp(buffer, "QUIT")) {
        close_socket(set, server);
        return EXIT_SUCCESS;
    } else if (!strncmp(buffer, "USER", 4)) {
        user(server, buffer + 5);
        return EXIT_SUCCESS;
    } else if (!strncmp(buffer, "PASS", 4)) {
        pass(server, buffer + 5);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
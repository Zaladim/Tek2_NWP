/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** help
*/

#include "server.h"

void help(server_t *server)
{
    dprintf(server->sock, "214 Available commands: USER PASS CWD CDUP QUIT \
    DELE PWD PASV PORT HELP NOOP RETR STOR\n");
}
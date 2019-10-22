/*
** EPITECH PROJECT, 2019
** MYFTP
** File description:
** pwd
*/

#include "server.h"

void pwd(server_t *server)
{
	dprintf(server->sock, "257 current folder is: \"%s\".\n", \
    getcwd(NULL, 0));
}
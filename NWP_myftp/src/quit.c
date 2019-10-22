/*
** EPITECH PROJECT, 2019
** MYFTP
** File description:
** Exit server
*/

#include "server.h"

void close_socket(set_t *set, server_t *server)
{
	int num = server->num_client;

	dprintf(server->sock, "221 Goodbye.\n");
	close(server->sock);
	FD_CLR(server->sock, &(set->all_fd));
	server->users[num]->fd = -1;
    server->users[num]->name = 0;
    server->users[num]->pass = 0;
	close(server->users[num]->data_fd);
    server->users[num]->data_fd = -1;
    close(server->users[num]->data_server_fd.fd);
    server->users[num]->data_server_fd.fd = -1;
}
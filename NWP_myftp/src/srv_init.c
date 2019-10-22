/*
** EPITECH PROJECT, 2019
** FTP SERVER
** File description:
** Initialise server
*/

#include "server.h"

int srv_init(server_t *server, int port)
{
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int opt = 1;

    if ((server->serv.fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        return (dprintf(2, "Socket failed\n"), EXIT_ERROR);
    if (setsockopt(server->serv.fd, SOL_SOCKET, \
        SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return (dprintf(2, "Socket setup failed\n"), EXIT_ERROR);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(server->serv.fd, (struct sockaddr *) &address, \
        sizeof(address)) < 0)
        return (dprintf(2, "Socket binding failed\n"), EXIT_ERROR);
    if (listen(server->serv.fd, 5) < 0)
        return (dprintf(2, "Socket listen failed\n"), EXIT_ERROR);
    getsockname(server->serv.fd, (struct sockaddr *) &address, &addrlen);
    server->serv.ip = inet_ntoa(address.sin_addr);
    server->serv.port = htons(port);
    return EXIT_SUCCESS;
}
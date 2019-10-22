/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** passive
*/

#include "server.h"

static void create_data_sock(server_t *server, int nb)
{
    struct sockaddr_in address;
    int fd;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        exit(dprintf(2, "Create socket failed\n", EXIT_ERROR));
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = (unsigned int) 0;
    if (bind(fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        exit(dprintf(2, "Binding socket failed\n", EXIT_ERROR));
    }
    if (listen(fd, 1) < 0) {
        exit(dprintf(2, "Listening socket failed\n", EXIT_ERROR));
    }
    server->users[nb]->data_server_fd.fd = fd;
}

static void set_socket_values(server_t *server, int nb)
{
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    getsockname(server->users[nb]->data_server_fd.fd, (struct sockaddr *) \
    &address, &addrlen);
    server->users[nb]->data_server_fd.ip = inet_ntoa(address.sin_addr);
    server->users[nb]->data_server_fd.port = htons(address.sin_port);
}

static void send_info(server_t *server, int nb)
{
    socket_t s = server->users[nb]->data_server_fd;
    char *cut;

    dprintf(server->users[nb]->fd, "227 Entering Passive Mode (");
    while ((cut = strtok(s.ip, ".")) != NULL) {
        dprintf(server->users[nb]->fd, "%s, ", cut);
    }
    dprintf(server->users[nb]->fd, "%d, %d)\n", s.port / 256, \
    s.port % 256);
}

static void wait_for_connection(server_t *server, int nb)
{
    int data_server_fd = server->users[nb]->data_server_fd.fd;

    if ((server->users[nb]->data_fd = accept(data_server_fd, \
    (struct sockaddr *) 0, (socklen_t *) 0)) < 0) {
        exit(dprintf(2, "Accept failed\n", EXIT_ERROR));
    }
}

void passive(server_t *server)
{
    create_data_sock(server, server->num_client);
    set_socket_values(server, server->num_client);
    send_info(server, server->num_client);
    wait_for_connection(server, server->num_client);
}
/*
** EPITECH PROJECT, 2019
** NWP_myftp_2018
** File description:
** retr
*/

#include "server.h"

static void read_file(server_t *server, char *path)
{
    FILE *file;
    char c;
    int n = server->num_client;

    if ((file = fopen(path, "r")) == NULL) {
        dprintf(server->users[n]->fd, "550 file error.\n");
        exit(EXIT_ERROR);
    }
    dprintf(server->users[n]->fd, "150 File status okay.\n");
    while ((c = fgetc(file)) != EOF)
        dprintf(server->users[n]->data_fd, "%c", c);
    fclose(file);
    dprintf(server->users[n]->fd, "226 Closing data connection.\n");
    exit(EXIT_SUCCESS);
}

static char *get_path(server_t *server, char *path, char *buff)
{
    getcwd(buff, 150);
    if (path[0] != '/')
        strcat(buff, "/");
    strcat(buff, path);
    return buff;
}

void retr(server_t *server, char *path)
{
    char buff[1024];
    int pid;

    if (server->users[server->num_client]->data_fd == -1) {
        dprintf(server->sock, "425 Data connection doesn't exist.\n");
        return;
    }
    get_path(server, path, buff);
    pid = fork();
    if (pid < 0){
        dprintf(2, "Fork error.\n");
        return;
    }
    if (pid == 0)
        read_file(server, buff);
    close(server->users[server->num_client]->data_fd);
    server->users[server->num_client]->data_fd = -1;
    close(server->users[server->num_client]->data_server_fd.fd);
    server->users[server->num_client]->data_server_fd.fd = -1;
}
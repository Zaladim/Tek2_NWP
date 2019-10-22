/*
** EPITECH PROJECT, 2019
** FTP SERVER
** File description:
** Const include
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>

static int EXIT_ERROR = 84;
static int NB_USER = 5;

typedef struct set {
    fd_set all_fd;
    fd_set cur_fd;
} set_t;

typedef struct socket {
    int fd;
    int port;
    char *ip;
} socket_t;

typedef struct user {
    int fd;
    int name;
    int pass;
    socket_t data_server_fd;
    int data_fd;
} user_t;

typedef struct server {
    socket_t serv;
    user_t **users;
    int sock;
    int num_client;
} server_t;

void test_error(int argc, char **argv);
int srv_init(server_t *server, int port);
int srv_run(server_t *server);
int client_connect(server_t *server, set_t *set);
int detect_command(set_t *set, server_t *server);
void close_socket(set_t *set, server_t *server);

int command_base(server_t *server, set_t *set, char *buffer);
int commands(server_t *server, char *buffer);

int user(server_t *server, char *buffer);
int pass(server_t *server, char *buffer);
void pwd(server_t *server);
void passive(server_t *server);
void active(server_t *server, char *path);
void retr(server_t *server, char *path);
void stor(server_t *server, char *buffer);
void list(server_t *server);
void dele(server_t *server, char *buffer);
void help(server_t *server);
void cwd(server_t *server, char *buffer);
void cdup(server_t *server);

#endif /* !SERVER_H_ */

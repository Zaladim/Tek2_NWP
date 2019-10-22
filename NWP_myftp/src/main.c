/*
** EPITECH PROJECT, 2019
** FTP SERVER
** File description:
** main
*/

#include "server.h"

int main(int argc, char **argv)
{
    server_t server;
    DIR* dir = opendir("mydir");

    test_error(argc, argv);
    if (srv_init(&server, atoi(argv[1])))
        return EXIT_ERROR;
    if ((dir = opendir(argv[2])))
        closedir(dir);
    else
        return (dprintf(2, "Incorrect path\n"), EXIT_ERROR);
    chdir(argv[2]);
    return srv_run(&server);
}
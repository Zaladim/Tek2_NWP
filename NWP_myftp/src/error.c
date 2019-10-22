/*
** EPITECH PROJECT, 2019
** FTP SERVER
** File description:
** Error handling
*/

#include "server.h"

void usage(void)
{
    printf("USAGE : ./myftp port path\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    printf("\tpath\tis the path to the home directory \
    for the Anonymous user\n");
}

void test_error(int argc, char **argv)
{
    if (argc == 2 && !strcmp(argv[1], "-help")) {
        usage();
        exit(EXIT_SUCCESS);
    }
    if (argc != 3) {
        dprintf(2, "Wrong number of arguments\n");
        exit(EXIT_ERROR);
    }
}
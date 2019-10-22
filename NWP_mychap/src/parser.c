/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Parser
*/

#include "mychap.h"

args_t *parser(int argc, char **argv)
{
    args_t *args = malloc(sizeof(args_t));

    if (argc != 7)
        return (dprintf(2, "Invalids arguments"), NULL);
    if (!args)
        return (dprintf(2, "Malloc : %s\n", strerror(errno)), NULL);
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0)
            args->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--target") == 0)
            args->target = argv[i + 1];
        if (strcmp(argv[i], "-P") == 0 || strcmp(argv[i], "--password") == 0)
            args->password = argv[i + 1];
    }
    if (strcmp(args->target, "localhost") == 0)
        args->target = "127.0.0.1";
    return args;
}
/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** main
*/

#include "arpspoof.h"

void display_error(const char *msg)
{
    dprintf(2, "%s\n", msg);
}

int main(int ac, char **av)
{
    data_t data;

    if (parser(ac, av, &data) || lexer(data))
        return FAILURE;
    return EXIT_SUCCESS;
}
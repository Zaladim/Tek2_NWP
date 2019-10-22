/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** parser
*/

#include "arpspoof.h"

static void display_usage(void)
{
    dprintf(2, "USAGE: ./myARPspoof sourceIP destIP Iface [--printBroacast|--\
printSpoof\n");
}

static int additionnal_params(int ac, char **av, data_t *data)
{
    if (ac == 4)
        return EXIT_SUCCESS;
    if (ac == 5 && !strcmp(av[4], "--printBroadcast"))
        data->p_broadcast = 1;
    else if (ac == 6 && !strcmp(av[4], "--printSpoof")) {
        data->p_spoof = 1;
        data->mac = av[5];
    } else
        return (display_usage(), FAILURE);
    return EXIT_SUCCESS;
}

int parser(int ac, char **av, data_t *data)
{
    if (ac == 2 && !strcmp(av[1], "-h"))
        return (display_usage(), 0);
    if (ac < 4 || ac > 6)
        return (display_usage(), FAILURE);
    data->source_ip = av[1];
    data->dest_ip = av[2];
    data->iface = av[3];
    data->p_broadcast = 0;
    data->p_spoof = 0;
    data->mac = "";
    return additionnal_params(ac, av, data);
}
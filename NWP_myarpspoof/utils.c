/*
** EPITECH PROJECT, 2019
** NWP_myarpspoof_2018
** File description:
** utils
*/

#include "arpspoof.h"

unsigned char *get_mac_from_iface(char *interface)
{
    int sd;
    struct ifreq ifr;
    unsigned char *res = NULL;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        display_error("Failed open socket");
        exit(FAILURE);
    }
    memset(&ifr, 0, sizeof(ifr));
    sprintf(ifr.ifr_name, "%s", interface);
    if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0) {
        display_error("Failed to get own mac addr");
        exit(FAILURE);
    }
    close(sd);
    if ((res = malloc(sizeof(unsigned char) * 6)) == NULL)
        exit(FAILURE);
    memcpy(res, ifr.ifr_hwaddr.sa_data, 6 * sizeof(unsigned char));
    return res;
}

char *get_own_ip(char *interface)
{
    int sd;
    struct ifreq ifr;
    char *res = NULL;

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed open socket");
        exit(FAILURE);
    }
    memset(&ifr, 0, sizeof(ifr));
    sprintf(ifr.ifr_name, "%s", interface);
    if (ioctl(sd, SIOCGIFADDR, &ifr) < 0) {
        display_error("Failed to get own ip");
        exit(FAILURE);
    }
    close(sd);
    res = inet_ntoa(((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr);
    return res;
}

unsigned int converted_ip(char *ip)
{
    unsigned int addr = 0;

    if ((addr = inet_addr(ip)) == INADDR_NONE) {
        display_error("Can't convert sender ip");
        exit(FAILURE);
    }
    return addr;
}

unsigned char *convert_mac(char *mac)
{
    unsigned char *res = malloc(6 * sizeof(unsigned char));

    if (!res)
        exit(84);
    memset(res, 0, 6 * sizeof(unsigned char));
    if (sscanf(mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &res[0], &res[1], \
    &res[2], &res[3], &res[4], &res[5]) != 6) {
        display_error("Wrong format for MAC address");
        exit(84);
    }
    return (unsigned char *) res;
}
/*
** EPITECH PROJECT, 2019
** MYCHAP
** File description:
** Include
*/

#ifndef MY_CHAP_H_
#define MY_CHAP_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <errno.h>
#include <sys/param.h>
#include <openssl/sha.h>

static int EXIT_ERROR = 84;
static int BUFF_LENGTH = 8192;
static int SHA_LENGTH = 10;
static char *HELLO = "client hello";
static int LEN_HELLO = 12;

typedef struct hdr {
    struct udphdr *udp;
    struct iphdr *ip;
} hdr_t;

typedef struct addr {
    struct sockaddr_in dest;
    struct sockaddr_in src;
} addr_t;

typedef struct args {
    uint16_t port;
    char *target;
    char *password;
} args_t;

typedef struct udphdr udphdr_t;
typedef struct iphdr iphdr_t;

int create_socket(int opt);
int create_header(hdr_t *hdr, args_t *args, int len);
void set_buffer(char *buffer, hdr_t *hdr, char *msg, int len);
void set_addr(addr_t *addr, args_t *args);
args_t *parser(int argc, char **argv);
char *hash(unsigned char *salt, unsigned char *msg, size_t n);
int reception(int fd, addr_t *addr, hdr_t *hdr, args_t *args);

#endif /* !MY_CHAP_H_ */
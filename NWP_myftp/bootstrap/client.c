/*
** EPITECH PROJECT, 2019
** FTP
** File description:
** Client
*/

#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h> 

int main(int argc, char **argv)
{
	struct sockaddr_in address;
	struct sockaddr_in saddr;
	int sock = 0;
	int port = atoi(argv[2]);
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		return 84;
	}
	memset(&saddr, '0', sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	if (inet_pton(AF_INET, argv[1], &saddr.sin_addr) <= 0) {
		perror("inet_pton");
		return 84;
	}
	if (connect(sock, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
		perror("connect");
		return 84;
	}
	read(sock, buffer, 1024);
	printf("Server said: %s\n", buffer);
}
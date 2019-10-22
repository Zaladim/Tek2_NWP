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
	int one = 1;
	const int *val = &one;
	int port = atoi(argv[2]);
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
		perror("Socket");
		return 84;
	}
	if (setsockopt (sock, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0){
		perror("Setsockopt");
		return 84;
	}
	return 0;
}
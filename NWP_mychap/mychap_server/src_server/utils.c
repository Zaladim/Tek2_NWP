/*
** utils.c for utils
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Wed Feb  6 19:07:45 2019 
** Last update Wed Feb  6 19:07:46 2019 
*/

#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include "server.h"

/*
** Listening on all interfaces on port 'port'.
*/
char			bind_server(int *sockfd, size_t port)
{
  struct sockaddr_in	server_address;

  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);
  if (bind(*sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)) != -1)
    return (1);
  perror("Could not assign a name to the socket");
  return (0);
}

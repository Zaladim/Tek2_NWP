/*
** server_udp.c for UDP Server
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Tue Nov 27 11:02:44 2018 
** Last update Tue Feb  5 18:04:02 2019 
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <openssl/rand.h>
#include <openssl/sha.h>
#include "list.h"
#include "server.h"

inline static void	usage(const char *prog_name)
{
  fprintf(stderr, "%s port\n", prog_name);
}


/*
** It will never really "block". If message did not arrive into socket for X reasons,
** then (at some point) another client will send a Phase 1 message ("client hello").
*/
static void	read_from_client(int sockfd, char *buffer, struct sockaddr_in *client_address)
{
  int		n;

  memset(client_address, 0, sizeof(struct sockaddr_in));
  memset(buffer, 0, MAXLINE);
  n = recvfrom(sockfd, (char *)buffer, MAXLINE,
	       MSG_WAITALL, (struct sockaddr *)client_address,
	       (socklen_t[1]){sizeof(struct sockaddr_in)});
  buffer[n] = 0;
}


/*
** Reads from client.
** Then checks if the connection exists.
** The connection can exist if the client has already
** sent Phase 1 (and that would mean that the client just sent Phase 3).
** If the connection is not found in the list, then it is added to the list
** and message Phase 2 is sent (Nonce).
** Else (if the connection is found), if the session hasn't expired, the
** server (calculates the response to the challenge and compares it against
** what it just received - Phase 3) and sends the response to the
** authentication (message Phase 4).
*/
static char		authentication_handshake(int sockfd)
{
  t_list		*list;
  char			*message_to_digest;
  char			buffer[MAXLINE];
  struct sockaddr_in	client_address;
  char			nonce[NONCE_LENGTH + 1] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 0};
  t_connection_info	*connection_object;

  if (!(list = list_create_empty())
      || !(message_to_digest = calloc(1, sizeof(char) * (NONCE_LENGTH + strlen(PASSWORD) + 1))))
    return (fprintf(stderr, "[-] Could not allocate mem\n"), 0);
  while ("forever")
    {
      read_from_client(sockfd, buffer, &client_address);
      if (!(connection_object = list_for_each(list, check_if_connection_exists, &client_address)))
	{
	  if (strcmp(PHASE1_MESG, buffer))
	    {
	      send_protocol_mismatch_message(sockfd, client_address);
	      list_remove(list, connection_object);
	      continue ;
	    }

	  print_server_authentication_step("(Phase 1 - RECV client hello)", buffer);
	  connection_object = init_and_send_challenge(sockfd, client_address, strdup(nonce));
	  list_push_front(list, connection_object);
	}
      else
	{
	  print_server_authentication_step("(Phase 3 - RECV response)", buffer);
	  if (strlen(buffer) == SHA256_DIGEST_LENGTH * 2)
	    {
	      if (time(NULL) - connection_object->timestamp < SESSION_TIMEOUT)
		send_authentication_result(sockfd, buffer, connection_object, message_to_digest);
	      else
		send_timeout_message(sockfd, connection_object);
	    }
	  else
	    send_protocol_mismatch_message(sockfd, connection_object->remote_client);
	  list_remove(list, connection_object);
	}
    }
  free(message_to_digest); /* never reached */
}


int			main(int argc, char *argv[])
{
  int			sockfd;

  if (argc != 2)
    return (usage(argv[0]), EXIT_FAILURE);
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
      perror("[-] Socket creation failed");
      return (EXIT_FAILURE);
    }
  if (!(bind_server(&sockfd, atoi(argv[1]))))
    return (EXIT_FAILURE);

  authentication_handshake(sockfd);

  /* never reached - should catch signal and free/close | Or let the OS do it :p */
  close(sockfd);
  return 0;
}

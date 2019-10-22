/*
** authentication.c for authentication
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Wed Feb  6 19:07:25 2019 
** Last update Wed Feb  6 19:07:26 2019 
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include "server.h"

inline __attribute__((always_inline))
void	print_server_authentication_step(const char *mesg_prepend, const char *mesg)
{
#ifdef _DEBUG_AUTH_STEPS
  fprintf(stdout, "%s: '%s'\n", mesg_prepend, mesg);
#endif /* !_DEBUG_AUTH_STEPS */
  (void)mesg_prepend;
  (void)mesg;
}


/*
** No error handling needed.
** Best-effort service -> best-effort delivery.
** If it manages to send to client_address, this is great.
** If it can't, well, it just can't, and it will not try again.
*/
inline static void	send_message(int sockfd, const char *message,
				     size_t length, struct sockaddr_in client_address)
{
  sendto(sockfd, message, length,
	 0, (const struct sockaddr *)&client_address,
	 sizeof client_address);
}


/*
** If more than SESSION_TIMEOUT seconds have elapsed between two messages (that means,
** message 1 and message 3 of the handshake), the server will send a "Session Timeout" message.
*/
void		send_timeout_message(int sockfd, t_connection_info *connection_object)
{
  const char	*response = SESSION_TIMEOUT_MSG;

  send_message(sockfd, response, strlen(response), connection_object->remote_client);
#ifdef _DEBUG
  fprintf(stdout, "Session Timeout\n");
#endif /* !_DEBUG */
}


void		send_protocol_mismatch_message(int sockfd, struct sockaddr_in client_address)
{
  const char	*response = PROTO_MISMATCH_MSG;

  send_message(sockfd, response, strlen(response), client_address);
#ifdef _DEBUG
  fprintf(stdout, "Protocol Mismach for <%s, %d>\n",
	  inet_ntoa(client_address.sin_addr),
	  ntohs(client_address.sin_port));
#endif /* !_DEBUG */
}


/*
** Upon new connection, instantiate a new object, fill infos,
** generate challenge and send it to client.
*/
t_connection_info	*init_and_send_challenge(int sockfd, struct sockaddr_in client_address,
						 char *nonce)
{
  t_connection_info	*connection_object;

  if (!(connection_object = malloc(sizeof(t_connection_info))))
    return (NULL);
#if RANDOM_NONCE
  if (!(RAND_bytes((unsigned char *)nonce, NONCE_LENGTH)))
    return (NULL);
#endif /* !STATIC_NONCE */
  connection_object->nonce = nonce;
  connection_object->remote_client = client_address;
  connection_object->timestamp = time(NULL);
  connection_object->challenge_response = NULL;

  /* Phase 2 - SEND Server Challenge (Nonce) */
  send_message(sockfd, (const char *)connection_object->nonce, NONCE_LENGTH, client_address);
  print_server_authentication_step("(Phase 2 - SEND Server Challenge (Nonce))", connection_object->nonce);
  return (connection_object);
}


/*
** This function calculates the answer to the challenge.
** It will then compare that answer against the response that the client sent.
** If it is equal, it means that the client response to the challenge is correct.
** The server also sends a message to the client indicating as to wether the authentication succeded or not.
*/
void		send_authentication_result(int sockfd, char *client_response,
					   t_connection_info *connection_object,
					   char *message_to_digest)
{
  char		*response;

  memset(message_to_digest, 0, NONCE_LENGTH + strlen(PASSWORD) + 1);
  strncpy(message_to_digest, (const char *)connection_object->nonce, NONCE_LENGTH);
  strncpy(message_to_digest + NONCE_LENGTH, PASSWORD, strlen(PASSWORD) + 1);
  connection_object->challenge_response = sha256((const char *)message_to_digest);

  response = memcmp(connection_object->challenge_response, client_response, SHA256_DIGEST_LENGTH * 2)
    ? "KO" : SECRET_PHRASE ;

  send_message(sockfd, response, strlen(response), connection_object->remote_client);
  print_server_authentication_step("(Phase 4 - SEND response)", response);
}

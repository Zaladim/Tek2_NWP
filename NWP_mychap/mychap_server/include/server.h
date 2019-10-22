#ifndef SERVER_H_
# define SERVER_H_

# include <sys/socket.h>
# include <netinet/in.h>
# include "list.h"

/*
** NEVER SEND OR RECV MORE THAN 1500 bytes as networks might do transparent/nontrasparent fragmentation.
** (The maximum frame size of Ethernet is 1518 bytes, 18 bytes of overhead (header and FCS),
** resulting in an MTU of 1500 bytes.
*/
# define MAXLINE		1024

# define NONCE_LENGTH		10
# define SESSION_TIMEOUT	5
# define SESSION_TIMEOUT_MSG	"Session Timeout"
# define PROTO_MISMATCH_MSG	"Protocol Mismatch"
# define PASSWORD		"epitech"
# define PHASE1_MESG		"client hello"
# define SECRET_PHRASE		"sh0k0Tresb0n"
# define RANDOM_NONCE		1

/*
** 'remote_client': contains information of the remote connection (client)
** 'nonce': contains a pseudorandom nonce generated with libssl (this is the challenge and it is sent to the client)
** 'challenge_response': contains the response to the challenge. This is what the client needs to calculate and send back.
**			 We calculate and store this as well on server side, to be able to compare the response of the client.
** 'timestamp': contains a timestamp of the connection (when the server received the first message). When sending the second
**			 message (Phase 3), the timestamp is check.
**			 If more than 'SESSION_TIMEOUT' seconds have elapsed, connection is dropped.
*/
typedef struct		s_connection_info
{
  struct sockaddr_in    remote_client;
  char			*nonce;
  char                  *challenge_response;
  time_t		timestamp;
}			t_connection_info;

/*
** src_server/hash.c
*/
char			*sha256(const char *str);

/*
** src_server/authentication.c
*/
void			send_authentication_result(int sockfd, char *client_response,
						   t_connection_info *, char *message_to_digest);
t_connection_info	*init_and_send_challenge(int sockfd, struct sockaddr_in client_address, char *nonce);
void			send_timeout_message(int sockfd, t_connection_info *);
void			print_server_authentication_step(const char *mesg_prepend, const char *mesg);
void			send_protocol_mismatch_message(int sockfd, struct sockaddr_in client_address);

/*
** src_server/utils.c
*/
char			bind_server(int *sockfd, size_t port);
t_connection_info	*list_check_if_exist(t_list * const list, void *arg);

#endif /* !SERVER_H_ */

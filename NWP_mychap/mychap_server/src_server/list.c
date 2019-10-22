/*
** list.c for list
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Wed Feb  6 19:07:36 2019 
** Last update Wed Feb  6 19:07:37 2019 
*/

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "server.h"

t_list		*list_create_empty(void)
{
  t_list	*list = malloc(sizeof(t_list));

  if (list != NULL)
    {
      list->list = NULL;
      list->size = 0;
    }
  return (list);
}

unsigned char	list_push_front(t_list * const list, void *data)
{
  t_node	*node;

  if (list == NULL
      || !(node = malloc(sizeof(t_node))))
    return (0);
  node->data = data;
  node->next = list->list;
  list->list = node;
  ++list->size;
  return (1);
}

unsigned int	list_remove(t_list * const list, void *data)
{
  t_node	*node;
  t_node	*node_prev;
  t_node	*delete;
  unsigned int	removed = 0;

  if (!list || !list->list)
    return (removed);
  node = list->list;
  node_prev = NULL;
  while (node)
    {
      if (node->data == data)
  	{
  	  delete = node;
  	  if (node_prev)
  	    node_prev->next = node->next;
  	  else
  	    list->list = node->next;
	  free(((t_connection_info *)delete->data)->challenge_response);
	  free(((t_connection_info *)delete->data)->nonce);
  	  free(delete);
  	  --list->size;
  	  ++removed;
  	  break ;
  	}
      node_prev = node;
      node = node->next;
    }
  return (removed);
}

/*
** Checking if the "signature" of the connection is present.
** The "signature" of the connection is made of a 2-tuple.
** For, TCP it is a 4-tuple. That is because we are processing all clients
** via the same socket (unlike TCP which implements reliability and needs
** most of the time separate sockets for each connection).
*/
char			check_if_connection_exists(void *uncasted_element, void *uncasted_connection_info)
{
  struct sockaddr_in	*connection_info = uncasted_connection_info;
  t_connection_info	*element = uncasted_element;

#ifdef _DEBUG
  fprintf(stdout, "element->ip: '%s'\n", inet_ntoa(element->remote_client.sin_addr));
  fprintf(stdout, "element->port: '%d'\n", ntohs(element->remote_client.sin_port));
  fprintf(stdout, "connection_info->ip: '%s'\n", inet_ntoa(connection_info->sin_addr));
  fprintf(stdout, "connection_info->port: '%d'\n", ntohs(connection_info->sin_port));
#endif /* !_DEBUG */
  return (element->remote_client.sin_addr.s_addr == connection_info->sin_addr.s_addr
	  && element->remote_client.sin_port == connection_info->sin_port);
}

void		*list_for_each(t_list * const list, t_node_action_fptr func, void *arg)
{
  t_node	*node;
  
  if (list != NULL && list->list != NULL && func != NULL)
    {
      node = list->list;
      while (node != NULL)
	{
	  if (func(node->data, arg))
	    return (node->data);
	  node = node->next;
	}
    }
  return (NULL);
}

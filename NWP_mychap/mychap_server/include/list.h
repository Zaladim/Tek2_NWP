#ifndef LIST_H_
# define LIST_H_

typedef struct	s_node
{
  void		*data;
  struct s_node	*next;
}		t_node;

typedef struct	s_list
{
  t_node	*list;
  unsigned int	size;
}		t_list;

typedef	        char(*t_node_action_fptr)(void *, void *);
typedef		int(*t_node_compare_fptr)(void *, void *);

t_list		*list_create_empty();
unsigned char	list_push_front(t_list * const, void *);
unsigned int	list_remove(t_list * const, void *);
void		*list_for_each(t_list * const list, t_node_action_fptr func, void *arg);
char		check_if_connection_exists(void *uncasted_element, void *uncasted_connection_info);

/* char				list_check_if_exist(t_list * const list, void *arg); */

#endif /* LIST_H_ */

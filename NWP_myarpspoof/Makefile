##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC	=	arp_packet.c	\
		lexer.c	\
		main.c	\
		parser.c	\
		print_opt.c	\
		spoofing.c	\
		utils.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I include -g3

NAME	=	myARPspoof

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)
	rm -rf *~
	rm -rf vgcore*

fclean:	clean
	rm -f $(NAME)

re:	fclean all $(NAME)

.PHONY:	all clean fclean re
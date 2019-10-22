##
## EPITECH PROJECT, 2018
## MYCHAP
## File description:
## Makefile
##

SRC			= 	src/main.c \
				src/hash.c \
				src/parser.c \
				src/create_hdr.c \
				src/socket.c \
				src/reception.c \
				src/setter.c


NAME		=	client

all:	$(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) -g3 -Iinclude -lcrypto
clean:
	rm -f *~
	rm -f *.o
	rm -f *#

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: fclean re all clean

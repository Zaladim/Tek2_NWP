##
## EPITECH PROJECT, 2019
## FTP SERVER
## File description:
## MAkefile
##

SRC			=	src/main.c \
				src/error.c \
				src/client_connect.c \
				src/srv_init.c \
				src/srv_run.c \
				src/quit.c \
				src/command_handler.c \
				src/active.c \
				src/commands.c \
				src/pwd.c \
				src/passive.c	\
				src/retr.c	\
				src/stor.c	\
				src/list.c	\
				src/dele.c	\
				src/log_in.c	\
				src/help.c	\
				src/directory_managment.c

OBJ			=	$(SRC:.c=.o)

FLAG		=	-Wall -Wextra -I./include

NAME		=	myftp

all:	$(NAME)

$(NAME):
	gcc	$(FLAG) $(SRC) -o $(NAME)

clean:
	rm -f *~
	rm -f *.o
	rm -f *#

fclean: clean
	rm -f $(NAME)

re:	fclean all
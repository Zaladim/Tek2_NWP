##
## Makefile for Makefile
## 
## Made by SRJanel
## Login SRJanel <n******.******s@epitech.eu>
## 
## Started on  Tue Nov 27 15:40:06 2018 
## Last update Tue Jan 29 17:13:07 2019 
##

SRC_SERVER	= src_server/server_udp.c \
		src_server/authentication.c \
		src_server/list.c \
		src_server/utils.c \
		src_server/hash.c \

OBJ_SERVER	= $(SRC_SERVER:.c=.o)

CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -D_DEBUG
CFLAGS		+= -D_DEBUG_OPTIONS #for client
CFLAGS		+= -D_DEBUG_AUTH_STEPS
CFLAGS		+= -pedantic-errors
CFLAGS		+= -I./include

CC		= gcc

LIBRARIES	+= -lcrypto

NAME_SERVER	= server

all: $(NAME_SERVER)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBRARIES) -o $(NAME_SERVER)

clean:
	$(RM) $(OBJ_SERVER) 

fclean: clean
	$(RM) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re

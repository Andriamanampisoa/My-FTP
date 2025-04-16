##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile for SBMLparser project
##

#################--- SRC ---#################

SRC	=	src/main.c							\
		src/help.c							\
		src/error/command_line_error.c		\
		src/server/init_server_struct.c		\
		src/server/setup_server.c			\
		src/server/connection_operations.c	\
		src/commands/command_management.c	\
		src/util/remove_r_and_n.c			\
		src/commands/quit_command.c			\
		src/commands/user_command.c			\
		src/commands/stor_command.c			\
		src/commands/retr_command.c			\
		src/commands/pwd_command.c			\
		src/commands/port_command.c			\
		src/commands/pasv_command.c			\
		src/commands/pass_command.c			\
		src/commands/noop_command.c			\
		src/commands/list_command.c			\
		src/commands/help_command.c			\
		src/commands/dele_command.c			\
		src/commands/cwd_command.c			\
		src/commands/cdup_command.c			\
		src/server/init_user_struct.c		\
		src/error/path_errors.c				\
		src/util/slash_utils.c				\

TEST	=

#################--- OBJ ---#################

OBJ	=	$(SRC:.c=.o)

TEST_OBJ	=	$(TEST:.c=.o)

#############################################

INCLUDE_PATH = include/

CFLAGS = -I$(INCLUDE_PATH) -W -Wall -Wextra -Wshadow -g

NAME	=	myftp

all:
			@echo -e "-----|\e[1;33mCompiling $(NAME)\e[0;m|-----"; \
			make start; \

start:	$(NAME)

$(NAME):	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS) -lm
			@echo -e "-----|\e[1;34mdone\e[0;m|-----"

%.o: %.c
	@echo "Compilation of $<"
	@if gcc -c -o $@ $< $(CFLAGS); then \
		echo -e "\033[0;34m[OK]\e[0;m | $@ <- $<"; \
	else \
		echo -e "\033[0;31m[FAILED]\e[0;m | $@ <- $<"; \
	fi

clean:
		@echo -e "-----|\e[1;33mClean repository\e[0;m|-----"
		rm -f $(OBJ)
		rm -f $(NAME)
		@echo -e "-----|\e[1;34mdone\e[0;m|-----"

fclean:	clean
		rm -f $(NAME)

re:	fclean all

tests_run:

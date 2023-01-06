# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 17:19:45 by mravera           #+#    #+#              #
#    Updated: 2023/01/06 02:57:05 by mravera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -g3 -fsanitize=address
#LIBS = -L Libft -L$(HOME)/.brew/opt/readline/lib -lft -ledit -lreadline -lhistory
# integration correct
LIBS = -L Libft -I /goinfre/mravera/.brew/Cellar/readline/8.2.1/include -L /goinfre/mravera/.brew/Cellar/readline/8.2.1/lib -lreadline -lft
RM = rm -rf
FOLDSRC = ./src/
SRC = ms_main.c \
			ms_supersplit.c \
			ms_utils.c \
			ms_utils_ii.c \
			ms_utilsiii.c \
			ms_echo.c \
			ms_pwd.c \
			ms_cd.c \
			ms_env.c \
			ms_enviii.c \
			ms_export.c \
			ms_setvar.c \
			ms_unset.c \
			ms_setsig.c \
			ms_parsing.c \
			ms_exec.c \
			ms_exec_builtins.c \
			ms_exec_redir.c \
			ms_exec_check_execve.c \
			ms_utils_exec.c \
			ms_close_pipes.c \
			ms_split_redir_utils.c \
			ms_exit.c \
			ms_error.c \
			ms_free.c \
			ms_lstcmd.c \
			ms_quote.c \
			ms_redirection.c \
			ms_strlen_utils.c \
			ms_check_dollar.c


OBJS = $(addprefix $(FOLDSRC), $(SRC:.c=.o))
UNAME = $(shell uname -s)

ifeq ($(UNAME), Linux)
	NPROC := $(shell nproc)
	CC = clang
	LIBS = -L Libft -L$(HOME)/.brew/opt/readline/lib -lft -lreadline -ltinfo
else
	NPROC := $(shell sysctl -n hw.ncpu)
	# CFLAGS += -I$(HOME)/.brew/opt/readline/include
endif

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	#$(MAKE) -C Libft
	$(MAKE) bonus -C Libft
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean :
	$(RM) $(NAME)

ffclean : clean
	$(MAKE) fclean -C Libft
	$(RM) $(NAME)

re : fclean all 

fre :ffclean all

.PHONY : all clean fclean ffclean re fre

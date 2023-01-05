# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 17:19:45 by mravera           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/01/05 21:29:46 by trerolle         ###   ########.fr        #
=======
#    Updated: 2023/01/05 21:43:24 by mravera          ###   ########.fr        #
>>>>>>> 08981e1ba6bc8c6907b218bb6ef66b28e99aeb1e
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
			ms_echo.c \
			ms_pwd.c \
			ms_cd.c \
			ms_env.c \
			ms_envii.c \
			ms_enviii.c \
			ms_envii.c \
			ms_export.c \
			ms_setvar.c \
			ms_unset.c \
			ms_alphaprint.c \
			ms_setsig.c \
			ms_parsing.c \
			ms_exec.c \
			ms_utils_exec.c \
			ms_exit.c \
<<<<<<< HEAD
			ms_strlen.c \
			ms_redirection.c \
			ms_quote.c
=======
			ms_free \
>>>>>>> 08981e1ba6bc8c6907b218bb6ef66b28e99aeb1e

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

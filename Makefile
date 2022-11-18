# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mravera <@student.42lausanne.ch>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 17:19:45 by mravera           #+#    #+#              #
#    Updated: 2022/11/18 17:31:44 by mravera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
FOLDSRC = ./src/

NAME = minishell

SRC = 

all = $(NAME)

$(NAME) : $(FOLDSRC) $(FOLDSRC)$(SRC:%.c=%.o)
	$(CC) $(CFLAGS) $^ -o $@

%.o : $(FOLDSRC)$(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(FOLDSRC)$(SRC:%.c=%.o)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 12:13:15 by ljustici          #+#    #+#              #
#    Updated: 2023/09/15 18:30:39 by ljustici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo

SRC_DIR		:= src/
_SRCS       := eat_utils.c \
				rout_utils.c \
				main.c \
				parse.c \
				time.c \
				routine.c \
				threads.c \

SRCS		:= ${addprefix ${SRC_DIR}, ${_SRCS}}
OBJS		:= $(SRCS:.c=.o)

CC          := @gcc
CFLAGS      := -Wall -Wextra -Werror

RM          := @rm -rf
MAKE        := @$(MAKE) --silent --no-print-directory

all:  $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(info created $(NAME))

clean:
	$(RM) $(OBJS)
	$(RM) obj
	$(info cleaned object files)

fclean: clean
	$(RM) $(NAME) checker
	$(info cleaned philosophers)

re: fclean all

.PHONY: all bonus clean fclean re
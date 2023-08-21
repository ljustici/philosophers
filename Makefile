# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 12:13:15 by ljustici          #+#    #+#              #
#    Updated: 2023/08/21 12:17:05 by ljustici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philosophers

SRCS        := src/*.c
OBJS		:= obj/*.o

CC          := @gcc
CFLAGS      := -Wall -Wextra -Werror -g

RM          := @rm -rf
MAKE        := @$(MAKE) --silent --no-print-directory

all:  $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS)
	$(info created $(NAME))

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	@mkdir -p obj
	@mv *.o obj
	$(info created object files)

clean:
	$(RM) $(OBJS)
	$(RM) obj
	$(info cleaned object files)

fclean: clean
	$(RM) $(NAME) checker
	$(info cleaned philosophers)

re: fclean all

.PHONY: all bonus clean fclean re
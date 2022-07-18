# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: insjang <insjang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 15:48:14 by insjang           #+#    #+#              #
#    Updated: 2022/07/18 15:48:18 by insjang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= philosophers.c \
		  arg_error_check.c \
		  src.c \
		  src2.c

OBJS	= $(SRCS:.c=.o)
HEAD	= philosophers.h

$(NAME) : $(OBJS)
	$(CC) $^ -o $(NAME)

all : $(NAME)

%.o : %.c $(HEAD)
	$(CC) $(CFLAGS) -c $(SRCS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

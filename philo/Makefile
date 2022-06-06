NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= philosophers.c \
		  arg_error_check.c \
		  src.c \
		  philo_action.c

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
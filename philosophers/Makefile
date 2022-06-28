NAME = philo

SRC = 	inits.c check.c time.c utils.c philo.c

HEADER = philo.h

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

%.o		:	%.c $(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@ 

clean	:	
			rm -rf $(OBJS)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

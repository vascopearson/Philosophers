SRCS = src/philosophers.c src/initialization.c src/utils.c src/thread_instructions.c src/actions.c src/free.c

OBJS = $(SRCS:.c=.o)

INC = inc/philosophers.h

CC = gcc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror -pthread #-fsanitize=address #-I$(HEADER)
HEADER = inc

%.o: %.c $(INC)
		$(CC) $(CFLAGS) -c $< -o $@

NAME = philo

all: $(NAME) $(OBJS) $(INC)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS) $(BONUS_OBJS) $(LIBFT)/*.o

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus
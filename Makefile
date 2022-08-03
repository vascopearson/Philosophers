SRCS = src/philosophers.c src/initialization.c src/utils.c src/thread_instructions.c src/actions.c

OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address -I$(HEADER)
HEADER = inc

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

NAME = philosophers

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS) $(BONUS_OBJS) $(LIBFT)/*.o

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus
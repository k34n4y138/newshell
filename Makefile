CC = clang -Wall -Werror -Wextra


SRC = main.c parsing_tools/parsing_tools.c env_tools/env_tools.c

OBJS = $(patsubst %.c,%.o,$(SRC))
HDRS = main.h parsing_tools/parsing_tools.h env_tools/env_tools.h


NAME = minishell
LIBFT = libft/libft.a

%.o: %.c $(HDRS)
	$(CC) $< -c  -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -lreadline $(OBJS) $(LIBFT) -o $(NAME)

all:$(NAME)

$(LIBFT):
	make -C libft bonus

clean:
	rm -rf $(OBJS)
	make -C libft fclean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re 
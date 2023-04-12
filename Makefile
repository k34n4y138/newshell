CC = clang  #-fsanitize=address -g


SRC = main.c parsing_tools/parsing_tools.c env_tools/env_store.c env_tools/env_crud.c

OBJS = $(patsubst %.c,%.o,$(SRC))
HDRS = main.h parsing_tools/parsing_tools.h env_tools/env_manager.h


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
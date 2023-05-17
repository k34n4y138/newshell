CC = clang -fsanitize=address -g

CFALGS = -Wall -Wextra -Werror


PARSING_SRC = parser/parser.c parser/tokenizers/token_expanders.c parser/tokenizers/token_splitters.c parser/tokenizers/tokenizer.c	parser/command_builders/command_builders.c
ENV_SRC = env_tools/env_crud.c env_tools/env_store.c
BUILTINS_SRC = 
EXECUTION_SRC =

SRC = main.c $(PARSING_SRC) $(ENV_SRC) $(BUILTINS_SRC) $(EXECUTION_SRC)

OBJS = $(patsubst %.c,%.o,$(SRC))
DEPS = $(patsubst %.c,%.d,$(SRC))



NAME = minishell
LIBFT = libft/libft.a

all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFALGS) $(OBJS) $(LIBFT)  -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD


$(LIBFT):
	@$(MAKE) -C libft> /dev/null
	@echo "Compiling libft"

clean:
	@$(MAKE) -C libft fclean > /dev/null
	@rm -f $(OBJS) $(DEPS)
	@echo "Removing Objects and Dep files"

fclean: clean
	@rm -f $(NAME)
	@echo "Removing $(NAME)"

re: fclean all
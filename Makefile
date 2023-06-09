CC = clang -fsanitize=address -g

CFALGS = -Wall -Wextra -Werror




PARSER_SRC = parser.c
TOKENIZER_SRC = token_expanders.c token_splitters.c tokenizer.c token_syntaxifiers.c token_mergers.c token_destructor.c
CMD_BUILDER_SRC = command_builders.c command_bhelpers.c command_destructor.c


PARSING_SRC = $(patsubst %.c,parser/%.c,$(PARSER_SRC)) $(patsubst %.c,parser/tokenizers/%.c,$(TOKENIZER_SRC)) $(patsubst %.c,parser/command_builders/%.c,$(CMD_BUILDER_SRC))

ENV_FILES = env_crud.c env_store.c
ENV_SRC = $(patsubst %.c,env_tools/%.c,$(ENV_FILES))


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
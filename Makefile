CC = clang #-fsanitize=address -g

CFLAGS = -Wall -Wextra -Werror




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

READLINE = readline/libreadline.a
RDLN_VER = 8.2
LBRDLN = -L./readline -lreadline  -lncurses

all: $(NAME)

-include $(DEPS)

$(NAME): $(READLINE) $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LBRDLN) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -I. -c  $< -o   $@ -MMD


$(LIBFT):
	@ echo "Compiling libft"
	@ make -C libft> /dev/null
	@ make -C libft clean> /dev/null
	@echo "Compiling libft"

clean:
	@ echo "Removing OBJS, Deps and libft"
	@ $(MAKE) -C libft fclean > /dev/null
	@ rm -f $(OBJS) $(DEPS)
	@ rm -rf readline

fclean: clean
	@ echo "Removing $(NAME) and readline"
	@ rm -f $(NAME)
	@ rm -f readline-$(RDLN_VER).tar.gz

$(READLINE):
	@ echo "Downloading readline"
	@ curl https://ftp.gnu.org/gnu/readline/readline-$(RDLN_VER).tar.gz -o readline-$(RDLN_VER).tar.gz > /dev/null
	@ echo "unpacking and compiling readline"
	@ tar -xvf readline-$(RDLN_VER).tar.gz > /dev/null
	@ mv readline-$(RDLN_VER) readline > /dev/null
	@ cd readline && ./configure > /dev/null
	@make -C readline > /dev/null

readline: $(READLINE)

re: fclean all readline
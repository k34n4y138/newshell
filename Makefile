CC = clang #-fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror

#====PARSING====#
PARSER_FILES = parser.c
TOKENIZER_FILES = token_expanders.c token_splitters.c tokenizer.c token_syntaxifiers.c token_mergers.c token_destructor.c
CMD_BUILDER_FILES = command_builders.c command_bhelpers.c command_destructor.c
PARSING_SRC = $(patsubst %.c,parser/%.c,$(PARSER_FILES)) $(patsubst %.c,parser/tokenizers/%.c,$(TOKENIZER_FILES)) $(patsubst %.c,parser/command_builders/%.c,$(CMD_BUILDER_FILES))

#====ENV====#
ENV_FILES = env_crud.c env_store.c
ENV_SRC = $(patsubst %.c,env_tools/%.c, $(ENV_FILES))

#====EXECUTION/BUILTINS====#
BUILTINS_FILES = bltn_env.c bltn_export.c bltn_unset.c
BUILTINS_SRC = $(patsubst %.c,executer/built_ins/%.c, $(BUILTINS_FILES))

#====EXECUTION====#
EXECUTION_FILES = exicution.c get_path.c utiles_get_path.c output_redirection.c input_redirection.c
EXECUTION_SRC = $(patsubst %.c,executer/%.c, $(EXECUTION_FILES)) 

#====MAIN====#
SRC = main.c $(PARSING_SRC) $(ENV_SRC) $(EXECUTION_SRC)
OBJS = $(patsubst %.c,%.o,$(SRC))
DEPS = $(patsubst %.c,%.d,$(SRC))

#====LIBS====#
LIBFT = libft/libft.a
READLINE = readline/libreadline.a
RDLN_VER = 8.2
LBRDLN = -L./readline -lreadline -lncurses


NAME = minishell


all: $(NAME)


-include $(DEPS)


$(NAME): $(READLINE) $(LIBFT) $(OBJS) 
	@ echo "Compiling $(NAME)"
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LBRDLN) executer/libft/libft.a executer/ft_printf/libftprintf.a -o $(NAME)


%.o: %.c
	@ echo "Compiling $@"
	@ $(CC) $(CFLAGS) -I. -c  $< -o $@ -MMD


$(LIBFT):
	@ echo "Compiling libft"
	@ make -C libft> /dev/null
	@ make -C libft clean> /dev/null


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
	@ curl https://ftp.gnu.org/gnu/readline/readline-$(RDLN_VER).tar.gz -o readline-$(RDLN_VER).tar.gz > /dev/null 2>&1
	@ echo "unpacking and configuring readline"
	@ tar -xvf readline-$(RDLN_VER).tar.gz > /dev/null 2>&1
	@ mv readline-$(RDLN_VER) readline
	@ cd readline && ./configure > /dev/null 2>&1
	@ echo "compiling readline"
	@ make -C readline > /dev/null 2>&1


readline: $(READLINE)


re: fclean all readline

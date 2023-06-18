NAME = libft.a

SRC = ft_isprint.c ft_memmove.c ft_calloc.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_toupper.c ft_isalnum.c ft_strlcat.c ft_strnstr.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcpy.c ft_strrchr.c ft_atoi.c ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlen.c ft_tolower.c ft_strncmp.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c

SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft.h
	@ar -rc $(NAME) $(OBJ)

%.o : %.c
	@$(CC) -Wall -Werror -Wextra -c $< -o $@

bonus:$(OBJ) $(OBJBONUS)
	@ar -rc $(NAME) $(OBJ) $(OBJBONUS)

clean:
	@rm -f *.o

fclean: clean
	@rm -f libft.a

re: fclean all

.PHONY : clean fclean all re bonus


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
AR		=	ar rcs
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -rf
# Dir and file names
NAME	=	libft.a
SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c \
			ft_printf_fd/ft_printf_fd.c \
			ft_printf_fd/ft_aux_printf.c \
			ft_strjoin_free.c \
			ft_strtok.c \
			ft_strndup.c 

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

BSRCS	=	ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c 

BOBJS	=	$(patsubst %.c,%.o,$(BSRCS))

#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $?

all: $(NAME)

bonus: $(NAME) $(BOBJS)
	$(AR) $?

# Removes objects
clean:
	$(RM) $(OBJS) $(BOBJS)

# Removes objects and executables
fclean: clean
	$(RM) $(NAME)

# Removes objects and executables and remakes
re: fclean all
#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
.PHONY: all bonus clean fclean re

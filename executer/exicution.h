#ifndef EXICTUION_H
#define EXICTUION_H

# include "../parser/command_builders/t_command.h"
# include "../env_tools/env_manager.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
#include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>


# define PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"
# define READ_END 0
# define WRITE_END 1

void	exicution(t_command *cmds, char **env);
char	*get_path(char **env, char *cmd0, int status);

#endif
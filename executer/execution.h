/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:22:38 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/24 10:25:47 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include "../parser/command_builders/t_command.h"
# include "../env_tools/env_manager.h"
# include "../libft/libft.h"
# include "built_ins/builtins.h"
# include <readline/readline.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

/**************************************************************/
/*                            DEFINES                         */
/**************************************************************/

# define READ_END 0
# define WRITE_END 1

/**************************************************************/
/*                            STRUCT                          */
/**************************************************************/

typedef struct s_herdoc
{
	char			*read;
	char			*read_2;
	char			*stor;
	t_command		*head;
	t_redirection	*redirect;
	pid_t			pid;
	int				status;
	int				pip[2];
}	t_herdoc;

/**************************************************************/
/*                    FUNCTION EXECUTION                      */
/**************************************************************/

t_redirection	*check_last_input_herdoc(t_command *cmd);
int				read_herdoc(t_command *cmd);
int				is_env(t_command *cmd);
void			check_singl_built(t_command *cmd);
void			check_built_in(t_command *cmd);
void			check_built_in(t_command *cmd);
void			execution(t_command *cmds);
char			*get_path(char *path, char *cmd0, int status);
void			exit_file(char *file_name);
int				is_dir(char *path);
void			check_cmd(t_command *cmd);
void			close_prev_pip(t_command *cmd);
void			wait_for_childs(t_command *cmd);
void			handl_input(t_command *cmd);
void			handl_output(t_command *cmd);
/// @brief expand filename and throw error if ambiguous
///  designed to be called from child after invoking fork 
char			*filename_expand(char	*ftoken);

#endif
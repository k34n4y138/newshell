/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_get_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:14:26 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/22 09:49:15 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void wait_for_childs(t_command *cmd)
{
	int status;

	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		cmd = cmd->next;
	}
	env_exit_status(status >> 8, 1);
}

void	close_prev_pip(t_command *cmd)
{
	if (cmd->redirs & REDIR_PIPEOUT)
		close(cmd->pip[WRITE_END]);
	if (cmd->redirs & REDIR_PIPEIN)
		close(cmd->prev->pip[READ_END]);
}

void	dup_herdoc(t_command *cmd)
{
	int	fd;

	fd = open(".stor_herdoc", O_RDONLY, 0644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (cmd->redirs & REDIR_PIPEIN)
		close(cmd->prev->pip[READ_END]);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i])
	{
		while (str[i] == to_find[i])
		{
			i++;
			if (to_find[i] == '\0')
				return (str);
		}
		str++;
		i = 0;
	}
	return (0);
}

int check_is_empty(char *cmd)
{
	while (*cmd)
	{
		if (*cmd != ' ' || *cmd != '\t')
			return (1);
		cmd++;
	}
	return (0);
}

void	check_cmd(t_command *cmd)
{
	if (cmd->argc == 0)
		exit(0);
	if (!check_is_empty(cmd->argv[0]))
	{
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd->argv[0]);
		exit (127);
	}
	if ((cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
			&& ft_strstr(cmd->argv[0], ".sh"))
		cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 1);
		else
			cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
	}
	else
		cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_get_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:14:26 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/23 10:40:46 by yowazga          ###   ########.fr       */
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
	else if (ft_strchr(cmd->argv[0], '/'))
		cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 1);
	else
		cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:46:10 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/24 17:34:39 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_env(t_command *cmd)
{
	if (cmd->argc == 0)
		return (0);
	if (!ft_strcmp(cmd->argv[0], "exit") || !ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "unset")
		|| !ft_strcmp(cmd->argv[0], "export"))
		return (1);
	return (0);
}

void	check_singl_built(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "exit"))
		bltn_exit(cmd, SINGL_EXIT);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		bltn_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		bltn_unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		bltn_cd(cmd);
}

void	check_built_in(t_command *cmd)
{
	if (cmd->argc == 0)
		return ;
	if (!ft_strcmp(cmd->argv[0], "pwd") || !ft_strcmp(cmd->argv[0], "PWD"))
		bltn_pwd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		bltn_exit(cmd, EXIT_WITH_PIP);
	else if (!ft_strcmp(cmd->argv[0], "env") || !ft_strcmp(cmd->argv[0], "ENV"))
		bltn_env(cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		bltn_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		bltn_unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo")
		|| !ft_strcmp(cmd->argv[0], "ECHO"))
		bltn_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		bltn_cd(cmd);
}

void	handl_redir_in_singl_env(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handl_output(cmd);
		handl_input(cmd);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
}

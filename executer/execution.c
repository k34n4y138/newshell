/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:31:09 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/21 18:04:53 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void read_herdoc(t_command *cmd)
{
	t_redirection *redirect;

	redirect = cmd->_redirects;
	if (!(cmd->redirs & REDIR_HEREDOC))
		return ;
	while (redirect)
	{
		read_lin(redirect);
		redirect = redirect->next;
	}
}

void check_herdoc(t_command *cmd)
{
	if (cmd->redirs & (REDIR_HEREDOC | REDIR_FILEIN))
			if (cmd->redirs & REDIR_HEREDOC)
				read_herdoc(cmd);
}

void check_built_in(t_command *cmd)
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
	else if (!ft_strcmp(cmd->argv[0], "echo") || !ft_strcmp(cmd->argv[0], "ECHO"))
		bltn_echo(cmd);
}

void	check_singl_built(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "exit"))
		bltn_exit(cmd, SINGL_EXIT);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		bltn_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		bltn_unset(cmd);
	// else if (!ft_strcmp(cmd->argv[0], "cd"))
	// 	bltn_unset(cmd);
}

void start_execution(t_command *cmd)
{
	handl_output(cmd);
	handl_input(cmd);
	cmd->envp = env_export();
	check_built_in(cmd);
	check_cmd(cmd);
	if (cmd->redirs & REDIR_PIPEOUT)
	{
		close(cmd->pip[READ_END]);
		close(cmd->pip[WRITE_END]);	
	}
	if (cmd->redirs & REDIR_PIPEIN)
		close(cmd->prev->pip[READ_END]);
	execve(cmd->path, cmd->argv, cmd->envp);
	ft_printf_fd(2, "minishell: %s\n", strerror(errno));
	exit (126);
}

int	is_env(t_command *cmd)
{
	if (cmd->argc == 0)
		return (0);
	if (!ft_strcmp(cmd->argv[0], "exit")|| !ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "unset") || !ft_strcmp(cmd->argv[0], "export"))
		return (1);
	return (0);
}

void execution(t_command *cmd)
{
	t_command *head;

	head = cmd;
	while (cmd)
	{
		if (!cmd->next && !cmd->prev && is_env(cmd))
		{
			check_singl_built(cmd);
			return ;
		}
		if (cmd->next != NULL && pipe(cmd->pip) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		read_herdoc(cmd);
		cmd->pid = fork();
		if (cmd->pid == -1)
			exit(EXIT_FAILURE);
		else if (cmd->pid == 0)
			start_execution(cmd);
		close_prev_pip(cmd);
		cmd = cmd->next;
	}
	wait_for_childs(head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exicution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:31:09 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 18:40:26 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exicution.h"

void	exit_file(char *file_name)
{
	ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
	exit(1);
}

void	read_herdoc(t_command *cmd)
{
	t_redirection	*redirect;

	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_HEREDOC)
			read_lin(redirect);
		redirect = redirect->next;
	}
}

void	start_execution(t_command *cmd)
{
	handl_output(cmd);
	handl_input(cmd);
	check_cmd(cmd);
	cmd->envp = env_export();
	execve(cmd->path, cmd->argv, cmd->envp);
}

void	wait_for_childs(t_command *cmd)
{
	int	status;

	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		cmd->exit_status = status >> 8;
		cmd = cmd->next;
	}
}

void	exicution(t_command *cmd)
{
	t_command	*head;

	head = cmd;
	while (cmd)
	{
		if (cmd->next != NULL && pipe(cmd->pip) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		if (cmd->redirs & (REDIR_HEREDOC | REDIR_FILEIN))
			if (cmd->redirs & REDIR_HEREDOC)
				read_herdoc(cmd);
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmd->pid == 0)
			start_execution(cmd);
		close_prev_pip(cmd);
		cmd = cmd->next;
	}
	wait_for_childs(head);
}

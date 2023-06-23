/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:31:09 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/23 16:17:44 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void sighandler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	close_fd_herdoc(t_command *cmd)
{
	t_command		*head;
	t_redirection	*redirect;

	head = cmd;
	while (head && (head->redirs & REDIR_HEREDOC))
	{
		redirect = head->_redirects;
		while (redirect && (redirect->type & REDIR_HEREDOC))
		{
			if (redirect->fd > 2)
				close(redirect->fd);
			redirect = redirect->next;
		}
		head = head->next;
	}
}

int	start_fork(t_command *cmd)
{
	if (!cmd->next && !cmd->prev && is_env(cmd))
	{
		check_singl_built(cmd);
		return(1);
	}
	if (cmd->next != NULL && pipe(cmd->pip) == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(EXIT_FAILURE);
	else if (cmd->pid == 0)
		start_execution(cmd);
	close_prev_pip(cmd);
	return (0);
}

void	execution(t_command *cmd)
{
	t_command	*head;

	head = cmd;
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (read_herdoc(cmd))
		return ;
	while (cmd)
	{
		if (start_fork(cmd))
			return ;
		cmd = cmd->next;
	}
	wait_for_childs(head);
	close_fd_herdoc(head);
}

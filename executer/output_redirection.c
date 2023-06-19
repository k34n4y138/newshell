/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:20:55 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 18:40:55 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exicution.h"


char	*expand_line(char *line);

t_redirection	*creat_out_file(t_redirection *redirect)
{
	t_redirection	*last_out;

	last_out = NULL;
	if (redirect->type & REDIR_FILEOUT)
	{
		redirect->fd = open(redirect->file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redirect->fd == -1)
			exit_file(redirect->file);
		last_out = redirect;
		close(redirect->fd);
	}
	else if (redirect->type & REDIR_FILEAPND)
	{
		redirect->fd = open(redirect->file,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (redirect->fd == -1)
			exit_file(redirect->file);
		last_out = redirect;
		close(redirect->fd);
	}
	return (last_out);
}

void	handl_out_file(t_command *cmd, t_redirection *last_out)
{
	if (last_out->type & REDIR_FILEOUT)
	{
		last_out->fd = open(last_out->file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (last_out->fd == -1)
			exit_file(last_out->file);
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
	}
	else if (last_out->type & REDIR_FILEAPND)
	{
		last_out->fd = open(last_out->file,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (last_out->fd == -1)
			exit_file(last_out->file);
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
	}
	if (cmd->redirs & REDIR_PIPEOUT)
		close(cmd->pip[WRITE_END]);
}

void	handl_output(t_command *cmd)
{
	t_redirection	*last_out;
	t_redirection	*redirect;

	redirect = cmd->_redirects;
	if (cmd->redirs & (REDIR_FILEOUT | REDIR_FILEAPND))
	{
		while (redirect)
		{
			if (redirect->type & REDIR_FILEIN)
			{
				if (access(redirect->file, F_OK) == -1)
					break ;
				redirect = redirect->next;
			}
			last_out = creat_out_file(redirect);
			redirect = redirect->next;
		}
		handl_out_file(cmd, last_out);
	}
	else if (cmd->redirs & REDIR_PIPEOUT)
	{
		dup2(cmd->pip[WRITE_END], STDOUT_FILENO);
		close(cmd->pip[WRITE_END]);
	}
}

void	read_lin(t_redirection *redirect)
{
	char	*read;
	char	*read_2;

	redirect->fd = open(".stor_herdoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		read_2 = readline("> ");
		read = expand_line(read_2);
		free(read_2);
		if (!read || ft_strnstr_1(read, redirect->file,
				ft_strlen(redirect->file)))
		{
			free(read);
			break ;
		}
		ft_putstr_fd(read, redirect->fd);
		write(redirect->fd, "\n", 1);
		free(read);
	}
	close(redirect->fd);
}

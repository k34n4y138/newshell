/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:20:55 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/23 10:12:46 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exit_file(char *file_name)
{
	ft_printf_fd(2, "minishell: %s: %s\n", file_name, strerror(errno));
	exit(1);
}

t_redirection	*creat_out_file(t_redirection *redirect)
{
	char			*file_name;

	file_name = filename_expand(redirect->file);
	if (redirect->type & REDIR_FILEOUT)
	{
		redirect->fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redirect->fd == -1)
			exit_file(redirect->file);
		close(redirect->fd);
	}
	else if (redirect->type & REDIR_FILEAPND)
	{
		redirect->fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (redirect->fd == -1)
			exit_file(redirect->file);
		close(redirect->fd);
	}
	free(file_name);
	return (redirect);
}

void	handl_out_file(t_redirection *last_out)
{
	char	*filename;

	filename = filename_expand(last_out->file);
	if (last_out->type & REDIR_FILEOUT)
	{
		last_out->fd = open(filename,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (last_out->fd == -1)
			exit_file(filename);
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
	}
	else if (last_out->type & REDIR_FILEAPND)
	{
		last_out->fd = open(filename,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (last_out->fd == -1)
			exit_file(filename);
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
	}
	free(filename);
}

void	handl_output(t_command *cmd)
{
	t_redirection	*last_out;
	t_redirection	*redirect;
	char			*file_name;

	redirect = cmd->_redirects;
	if (cmd->redirs & (REDIR_FILEOUT | REDIR_FILEAPND))
	{
		while (redirect)
		{
			if (redirect->type & REDIR_FILEIN)
			{
				file_name = filename_expand(redirect->file);
				if (access(file_name, F_OK) == -1)
					return ;
				free(file_name);
			}
			if (redirect->type & (REDIR_FILEOUT | REDIR_FILEAPND))
				last_out = creat_out_file(redirect);
			redirect = redirect->next;
		}
		handl_out_file(last_out);
	}
	else if (cmd->redirs & REDIR_PIPEOUT)
		dup2(cmd->pip[WRITE_END], STDOUT_FILENO);
}

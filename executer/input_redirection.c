/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:19:43 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 18:20:30 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exicution.h"

t_redirection	*check_last_input_file(t_command *cmd)
{
	t_redirection	*last_infile;
	t_redirection	*redirect;

	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_FILEIN)
			last_infile = redirect;
		redirect = redirect->next;
	}
	return (last_infile);
}

void	dup_in_file(t_command *cmd)
{
	t_redirection	*last_in_file;

	last_in_file = check_last_input_file(cmd);
	last_in_file->fd = open(last_in_file->file, O_RDONLY, 0644);
	if (last_in_file->fd == -1)
		exit_file(last_in_file->file);
	dup2(last_in_file->fd, STDIN_FILENO);
	close(last_in_file->fd);
	if (cmd->redirs & REDIR_PIPEIN)
		close(cmd->prev->pip[READ_END]);
}

int	which_last_input(t_command *cmd)
{
	int				last_in;
	t_redirection	*redirs;

	redirs = cmd->_redirects;
	while (redirs)
	{
		if (redirs->type & (REDIR_FILEIN | REDIR_HEREDOC))
			last_in = redirs->type;
		redirs = redirs->next;
	}
	if (last_in & REDIR_FILEIN)
		return (REDIR_FILEIN);
	return (REDIR_HEREDOC);
}

void	check_infile(t_command *cmd)
{
	t_redirection	*redirect;

	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_FILEIN)
		{
			redirect->fd = open(redirect->file, O_RDONLY, 0644);
			if (redirect->fd == -1)
				exit_file(redirect->file);
			close(redirect->fd);
		}
		redirect = redirect->next;
	}
}

void	handl_input(t_command *cmd)
{
	if (cmd->redirs & (REDIR_HEREDOC | REDIR_FILEIN))
	{
		if (cmd->redirs & REDIR_FILEIN)
			check_infile(cmd);
		if (which_last_input(cmd) & REDIR_FILEIN)
			dup_in_file(cmd);
		else
			dup_herdoc(cmd);
	}
	else if (cmd->redirs & REDIR_PIPEIN)
	{
		dup2(cmd->prev->pip[READ_END], STDIN_FILENO);
		close(cmd->prev->pip[READ_END]);
	}
}

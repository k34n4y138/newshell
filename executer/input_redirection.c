/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:19:43 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/24 10:50:26 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// function is defined in parser/tokenizer/token_expanders.c
// char	*expand_line(char *line);
// TODO: expand filename
// char	*filename = expand_line(redirect->file);
// TODO: check if check_if_ambigous
// if (redirect->type & FILE_CHECK_AMBIGOUS && ft_strchr(filename, ' '))
// 		ft_printf_fd(2, "minishell: %s: ambiguous redirect\n", redirect->file)`

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
	char			*filename;

	last_in_file = check_last_input_file(cmd);
	filename = filename_expand(last_in_file->file);
	last_in_file->fd = open(filename, O_RDONLY, 0644);
	free(filename);
	if (last_in_file->fd == -1)
		exit_file(last_in_file->file);
	dup2(last_in_file->fd, STDIN_FILENO);
	close(last_in_file->fd);
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
	char			*filename;

	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_FILEIN)
		{
			filename = filename_expand(redirect->file);
			redirect->fd = open(filename, O_RDONLY, 0644);
			free(filename);
			if (redirect->fd == -1)
				exit_file(redirect->file);
			close(redirect->fd);
		}
		redirect = redirect->next;
	}
}

void	handl_input(t_command *cmd)
{
	t_redirection	*check_last_in_her;

	if (cmd->redirs & (REDIR_HEREDOC | REDIR_FILEIN))
	{
		if (cmd->redirs & REDIR_FILEIN)
			check_infile(cmd);
		if (which_last_input(cmd) & REDIR_FILEIN)
			dup_in_file(cmd);
		else
		{
			check_last_in_her = check_last_input_herdoc(cmd);
			dup2(check_last_in_her->fd, STDIN_FILENO);
			close(check_last_in_her->fd);
		}
	}
	else if (cmd->redirs & REDIR_PIPEIN)
		dup2(cmd->prev->pip[READ_END], STDIN_FILENO);
}

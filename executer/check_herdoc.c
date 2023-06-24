/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_herdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:47:48 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/24 10:48:07 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*expand_line(char *line);

t_redirection	*check_last_input_herdoc(t_command *cmd)
{
	t_redirection	*last_infile;
	t_redirection	*redirect;

	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_HEREDOC)
			last_infile = redirect;
		redirect = redirect->next;
	}
	return (last_infile);
}

void	read_data(t_redirection *redirect, t_herdoc *hed)
{
	hed->read_2 = readline("> ");
	if (!(redirect->type & HRDC_NO_EXPAND) && hed->read_2)
	{
		hed->read = expand_line(hed->read_2);
		free(hed->read_2);
	}
	else
		hed->read = hed->read_2;
}

void	start_read_herdoc(t_redirection *redirect, int *pip)
{
	t_herdoc	hed;

	hed.stor = ft_calloc(1, 1);
	close(pip[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		read_data(redirect, &hed);
		if (!hed.read || !ft_strcmp(redirect->file, hed.read))
		{
			free(hed.read);
			break ;
		}
		hed.stor = ft_strjoin_free(hed.stor, hed.read, 1, 1);
		hed.stor = ft_strjoin_free(hed.stor, "\n", 1, 0);
	}
	write(pip[1], hed.stor, ft_strlen(hed.stor));
	close(pip[1]);
	exit(0);
}

int	read_herdoc(t_command *cmd)
{
	t_herdoc	hrd;

	hrd.head = cmd;
	while (hrd.head && (hrd.head->redirs & REDIR_HEREDOC))
	{
		hrd.redirect = hrd.head->_redirects;
		while (hrd.redirect && (hrd.redirect->type & REDIR_HEREDOC))
		{
			if (pipe(hrd.pip) == -1)
				exit(EXIT_FAILURE);
			hrd.pid = fork();
			if (hrd.pid == -1)
				exit(EXIT_FAILURE);
			else if (hrd.pid == 0)
				start_read_herdoc(hrd.redirect, hrd.pip);
			hrd.redirect->fd = hrd.pip[0];
			close(hrd.pip[1]);
			waitpid(hrd.pid, &hrd.status, 0);
			if (hrd.status & 0x7F)
				return (1);
			hrd.redirect = hrd.redirect->next;
		}
		hrd.head = hrd.head->next;
	}
	return (0);
}

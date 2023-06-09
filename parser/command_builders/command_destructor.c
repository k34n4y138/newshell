/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_destructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:29:53 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/09 20:26:15 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_command.h"
#include <stdlib.h>

void	destroy_redirections(t_redirection	*redirs)
{
	t_redirection	*trgt;

	while (redirs && redirs->prev)
		redirs = redirs->prev;
	while (redirs)
	{
		trgt = redirs;
		redirs = redirs->next;
		if (trgt->file)
			free(trgt->file);
		free(trgt);
	}
}

void	destroy_commands(t_command	*cmd)
{
	char		*fargv;
	t_command	*trgt;

	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		trgt = cmd;
		cmd = cmd->next;
		destroy_redirections(trgt->_redirects);
		while (trgt->argc)
			free(trgt->argv[--trgt->argc]);
		free(trgt->argv);
		free(trgt);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bhelpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:06:07 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/08 18:08:50 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_builders.h"

int	calc_argc(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != TOK_PIPE)
	{
		if (token->type & TOK_REDIRS)
			token = token->next;
		else
			count++;
		token = token->next;
	}
	return (count);
}

void	appnd_to_chain(t_command **chain, t_command *com)
{
	t_command	*tmp;

	if (!*chain)
	{
		*chain = com;
		return ;
	}
	tmp = *chain;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = com;
	com->prev = tmp;
}

void	append_redir(t_redirection *redir, t_command *com)
{
	t_redirection	*tmp;

	if (!com->_redirects)
	{
		com->_redirects = redir;
		return ;
	}
	tmp = com->_redirects;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
	redir->prev = tmp;
}

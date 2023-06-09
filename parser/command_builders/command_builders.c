/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:10:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/09 20:24:06 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_builders.h"
#include "../../libft/libft.h"

//  the following 3 auxilary functions are defined in command_bhelpers.c

int		calc_argc(t_token	*token);
void	appnd_to_chain(t_command **chain, t_command *com);
void	append_redir(t_redirection *redir, t_command *com);

/// @brief  aux function to create redirection struct 
t_token	*handle_redirection(t_token *token, t_command	*com)
{
	t_redirection	*redir;

	redir = ft_calloc(1, sizeof(t_redirection));
	redir->type = token->type;
	redir->file = ft_strdup(token->next->token);
	com->redirs |= token->type;
	append_redir(redir, com);
	return (token->next);
}

/// @brief aux function to create pipe redirection struct
///        either PIPEIN or PIPEOUT 
void	handle_pipe(t_command	*com, int type)
{
	t_redirection	*redir;

	redir = ft_calloc(1, sizeof(t_redirection));
	redir->type = type;
	com->redirs |= type;
	append_redir(redir, com);
}

/// @brief function that translates tokens into commands
///	-# creates redirection structs for literals with TOK_REDIRS predesessor
///	-# append stand alone literals to argv
///	-# if pipe is found at the end it creates a PIPEOUT redirection struct
///	-# pipe token must be the first token in the next command in order for later
///          to have a PIPEIN redirection struct
t_token	*new_command(t_token *token, t_command **chain)
{
	t_command	*com;

	com = ft_calloc(1, sizeof(t_command));
	if (token && token->type == TOK_PIPE)
	{
		handle_pipe(com, REDIR_PIPEIN);
		token = token->next;
	}
	com->argv = ft_calloc(calc_argc(token) + 1, sizeof(char *));
	while (token && token->type != TOK_PIPE)
	{
		if (token->type & TOK_REDIRS)
			token = handle_redirection(token, com);
		else
			com->argv[com->argc++] = ft_strdup(token->token);
		token = token->next;
	}
	if (token && token->type == TOK_PIPE)
		handle_pipe(com, REDIR_PIPEOUT);
	appnd_to_chain(chain, com);
	return (token);
}

/// @brief  Builds a linked list of commands from a linked list of tokens
t_command	*build_commandchain(t_token *token)
{
	t_command	*chain;

	chain = NULL;
	while (token)
		token = new_command(token, &chain);
	return (chain);
}

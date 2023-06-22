/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntaxifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:41:12 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/21 19:55:00 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "t_token.h"
#include <stdio.h>

/// @brief check if the quote is closed 
int	quote_syntaxifier(t_token *token)
{
	if (!ft_strchr(token->raw + 1, token->raw[0]))
		return (0);
	return (1);
}

/// @brief check if the redirection is followed by a valid token
int	redir_syntaxifier(t_token *token)
{
	if (token->next
		&& token->next->type & (TOK_LITERAL | TOK_DBLQ | TOK_SNGQ | TOK_VAR))
		return (1);
	return (0);
}

int	syntax_error(t_token *token)
{
	printf("syntax error near unexpected token ");
	if (token)
		printf("`%s'\n", token->raw);
	else
		printf("`newline'\n");
	return (1);
}

int	unmatched_quote(t_token *token)
{
	printf("unexpected EOF while looking for matching ");
	printf("`%c'\n", token->raw[0]);
	return (1);
}

/// @brief check for unexepected token and unmatched quotes
int	syntaxifier(t_token *tokens)
{
	t_token		*token;

	token = tokens;
	while (token)
	{
		if (token->type & (TOK_DBLQ | TOK_SNGQ) && !quote_syntaxifier(token))
			return (unmatched_quote(token));
		else if (token->type & TOK_REDIRS && !redir_syntaxifier(token))
			return (syntax_error(token->next));
		else if (token->type & TOK_PIPE && !token->prev)
			return (syntax_error(token));
		else if (token->type & TOK_PIPE && !token->next)
			return (syntax_error(NULL));
		else if (token->type & TOK_PIPE && token->next->type & TOK_PIPE)
			return (syntax_error(token->next));
		token = token->next;
	}
	return (0);
}

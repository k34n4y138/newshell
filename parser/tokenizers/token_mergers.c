/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_mergers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:50 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/12 23:24:04 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "t_token.h"

// prototype declared here to not trigger a circular dependency

t_token	*tokenizer(char *line, bool subtok);
char	*expand_line(char *line);

bool	is_bltn_export_context(t_token	*token)
{
	while (token && token->type != TOK_PIPE)
	{
		if (token->type == TOK_LITERAL
			&& !ft_strncmp(token->token, "export", 6)
			&& (
				!token->prev
				|| !(token->prev->type & TOK_REDIRS)
			)
		)
			return (true);
		token = token->prev;
	}
	return (false);
}

void	replace_token(t_token	*tkn, t_token *new_token)
{
	t_token	*traveler;

	if (!new_token)
	{
		tkn->skip_expand = true;
		return ;
	}
	free(tkn->raw);
	free(tkn->token);
	traveler = new_token;
	while (traveler->next)
		traveler = traveler->next;
	new_token->prev = tkn->prev;
	traveler->next = tkn->next;
	traveler->space_after = tkn->space_after;
	*tkn = *new_token;
	free(new_token);
}

/// @brief aux function to handle variable tokens
///		   normally variable tokens are expanded and subtokenized
///        variable tokens won't be expanded if prev is HRDC
///        variable tokens won't be subtokenized if in context of export 
///  export context is when the token is after a literal with = sign in it
///   and the first literal without redirection behind it matches "export"
t_token	*aux_handle_vartok(t_token	*token)
{
	token->type = TOK_LITERAL;
	if (token->prev
		&& (token->prev->type == TOK_HRDC
			|| (token->prev->type == TOK_LITERAL && !token->prev->space_after
				&& token->prev->prev && token->prev->prev->type == TOK_HRDC)
		)
	)
	{
		token->token = ft_strdup(token->raw);
		return (token->prev);
	}
	token->token = expand_line(token->raw);
	if (token->prev
		&& token->prev->space_after == false
		&& token->prev->type & TOK_LITERAL
		&& ft_strchr(token->prev->token, '=')
		&& is_bltn_export_context(token)
	)
		return (token->prev);
	replace_token(token, tokenizer(token->token, true));
	if (token->prev)
		return (token->prev);
	return (token);
}

/// @brief aux function to merge a token with the next one
///        merged token enhirites the next token's space_after
///        and the next token is removed from the list
///        new token is returned to check if mergable with the new next
t_token	*aux_merge_next(t_token *token)
{
	t_token	*tmp;

	token->token = ft_strjoin_free(token->token,
			token->next->token, 1, 1);
	token->space_after = token->next->space_after;
	tmp = token->next;
	token->next = token->next->next;
	free(tmp->raw);
	free(tmp);
	token->skip_expand = false;
	if (token->next)
		token->next->prev = token;
	return (token);
}

/// @brief merge tokens that are next to each other and are literals
///        and manage expansion and subtokenization of variable tokens
void	merge_tokens(t_token *tk)
{
	while (tk)
	{
		if (tk->next
			&& tk->space_after == false
			&& tk->type & (TOK_LITERAL | TOK_DBLQ | TOK_SNGQ)
			&& tk->next->type & (TOK_LITERAL | TOK_DBLQ | TOK_SNGQ)
		)
			tk = aux_merge_next(tk);
		else if (tk->type & TOK_VAR)
			tk = aux_handle_vartok(tk);
		else
			tk = tk->next;
	}
}

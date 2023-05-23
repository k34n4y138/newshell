/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_mergers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:14:50 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/23 16:20:40 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../libft/libft.h"
#include "t_token.h"
t_token	*tokenizer(char *line, bool subtok);
char	*expand_line(char *line);
/// @brief aux funciton for TOK_VAR handler, traverse through the parents of the token to see if there's an Expand Command
/// @param  
/// @return 
bool	is_bltn_export_context(t_token	*token)
{
	int	REDIR_MASK;

	REDIR_MASK = TOK_HRDC | TOK_FILEAPND | TOK_FILEIN | TOK_FILEAPND;
	while (token && !(token->type & TOK_PIPE))
	{
		// printf("checking token: %s\n", token->token);
		if (token->type & TOK_LITERAL
		&& !ft_strncmp(token->token, "export", 6)
		&& (
			!token->prev
			|| !(token->prev->type & REDIR_MASK)
		))
			return (true);
		token = token->prev;
	}
		
	return (false);
}

void	replace_token(t_token	*tkn, t_token *new_token)
{
	t_token	*traveler;

	if (!new_token)
		return ;
	free(tkn->raw);
	free(tkn->token);
	traveler = new_token;
	while(traveler->next)
		traveler = traveler->next;
	new_token->prev = tkn->prev;
	traveler->next = tkn->next;
	traveler->space_after = tkn->space_after;
	*tkn = *new_token;
}

/// @brief  aux function for the merge_tokens function to treat variable tokens.
/// generally, Variable tokens are expanded and subtokenized.
///	the variable won't be expanded if it's preceded by a HRDC token;
/// the variable won't be subtokenized if it's preceeded by a literal variable with = in its ->token
///  	and if the first literal token that's 
t_token	*aux_handle_vartok(t_token	*token)
{

	token->type = TOK_LITERAL;
	if (token->prev && token->prev->type & TOK_HRDC)
	{
		token->token = ft_strdup(token->raw);
		return (token);
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




t_token	*aux_merge_next(t_token *token)
{
	t_token	*tmp;
	token->token = ft_strjoin_free(token->token, token->next->token, 1, 1);
	token->space_after = token->next->space_after;
	tmp = token->next;
	token->next = token->next->next;
	free(tmp->raw);
	free(tmp);
	if (token->next)
		token->next->prev = token;
	return (token);
}


/// @brief  finalize token treatment joining literal tokens that're not separated by spaces
///	if it encounters a variable token it will pass it to its aux function that'll treat the variable and decide the loops next step
/// @param token 


void	merge_tokens(t_token *tk)
{
	while (tk)
	{
		if (tk->next
		&& tk->space_after == false
		&& tk->type & (TOK_LITERAL | TOK_DBLQ | TOK_SNGQ)
		&& tk->next->type & (TOK_LITERAL | TOK_DBLQ | TOK_SNGQ))
			tk = aux_merge_next(tk);
		else if (tk->type & TOK_VAR)
			tk = aux_handle_vartok(tk);
		else 
			tk = tk->next;
	}
}
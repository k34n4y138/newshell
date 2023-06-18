/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:55:27 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/15 18:39:23 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "t_token.h"
#include "_token_splitters.h"

void	append_token(t_token	*token, t_token **list)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = token;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	token->prev = tmp;
	tmp->next = token;
	return ;
}

/// @brief given that line starts with (qt), it will substr till next (qt)
int	split_quote(char	*line, char qt, t_token **tokens)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	tkn->len = 1;
	while (line[tkn->len] && line[tkn->len] != qt)
		tkn->len++;
	if (line[tkn->len])
		tkn->len++;
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (ft_strchr(" \t", tkn->raw[tkn->len]))
		tkn->space_after = true;
	tkn->type = TOK_SNGQ;
	if (qt == '"')
		tkn->type = TOK_DBLQ;
	append_token(tkn, tokens);
	return (tkn->len);
}

/// @brief substr till space or a special character
/// @param subtok if true, will split by spaces only, ignoring other characters
///        subtok is used after expanding variable tokens 
int	split_literal(char *line, t_token **tokens, bool subtok)
{
	t_token	*tkn;
	char	*match;

	match = "'\"$<>| \t";
	if (subtok)
		match = " \t";
	tkn = ft_calloc(1, sizeof(t_token));
	while (line[tkn->len] && !ft_strchr(match, line[tkn->len])
	)
		tkn->len++;
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (subtok)
		tkn->token = ft_strdup(tkn->raw);
	if (ft_strchr(" \t", tkn->raw[tkn->len]))
		tkn->space_after = true;
	tkn->type = TOK_LITERAL;
	append_token(tkn, tokens);
	return (tkn->len);
}

int	split_dollar(char	*line, t_token **tokens)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	tkn->len = 1;
	while (line[tkn->len] == '_' || ft_isalnum(line[tkn->len]))
			tkn->len++;
	if (line[1] == '?')
		tkn->len = 2;
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (ft_strchr(" \t", tkn->raw[tkn->len]))
		tkn->space_after = true;
	tkn->type = TOK_VAR;
	append_token(tkn, tokens);
	return (tkn->len);
}

int	split_redirection(char	*line, int toklen, t_token **tokens)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	tkn->len = toklen;
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (ft_strncmp(tkn->raw, "|", 1) == 0)
		tkn->type = TOK_PIPE;
	else if (ft_strncmp(tkn->raw, "<<", 2) == 0)
		tkn->type = TOK_HRDC;
	else if (ft_strncmp(tkn->raw, ">>", 2) == 0)
		tkn->type = TOK_FILEAPND;
	else if (ft_strncmp(tkn->raw, "<", 1) == 0)
		tkn->type = TOK_FILEIN;
	else if (ft_strncmp(tkn->raw, ">", 1) == 0)
		tkn->type = TOK_FILEOUT;
	if (ft_strchr(" \t", tkn->raw[tkn->len]))
		tkn->space_after = true;
	tkn->token = ft_strdup(tkn->raw);
	append_token(tkn, tokens);
	return (tkn->len);
}

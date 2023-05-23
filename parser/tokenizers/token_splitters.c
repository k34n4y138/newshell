/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_splitters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:55:27 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/23 16:23:45 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "t_token.h"
#include "_tokenizers.h"


int	append_token(t_token	*token, t_token **list)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = token;
		return (1);
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	token->prev = tmp;
	tmp->next = token;
	return (1);
}

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
	if (line[tkn->len] == ' ')
		tkn->space_after = true;
	tkn->type = TOK_SNGQ;
	if (qt == '"')
		tkn->type = TOK_DBLQ;
	append_token(tkn, tokens);
	return (tkn->len);
}

int	split_literal(char *line, t_token **tokens, bool subtok)
{
	t_token	*tkn;
	char	*match;

	if (subtok)
		match = " ";
	else
		match = "'\"$<>| ";
	tkn = ft_calloc(1, sizeof(t_token));
	while (line[tkn->len] && !ft_strchr(match, line[tkn->len])
	)
		tkn->len++;
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (subtok)
		tkn->token = ft_strdup(tkn->raw);
	if (line[tkn->len] == ' ')
		tkn->space_after = true;
	tkn->type = TOK_LITERAL;
	append_token(tkn, tokens);
	return (tkn->len);
}

int	split_dollar(char	*line, t_token **tokens)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	while (line[tkn->len] == '$'
		|| line[tkn->len] == '_' || ft_isalnum(line[tkn->len]))
			tkn->len++;
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (line[tkn->len] == ' ')
		tkn->space_after = true;
	tkn->type = TOK_VAR;
	append_token(tkn, tokens);
	return (tkn->len);
}


int	split_redirection(char	*line, int toklen, t_token **tokens)
{
	char	*redirection;
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
	if (line[tkn->len] == ' ')
		tkn->space_after = true;
	tkn->token = ft_strdup(tkn->raw);
	append_token(tkn, tokens);
	return (tkn->len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expanders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:21:50 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/17 20:24:09 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"
#include "t_token.h"

t_token	*tokenizer(char *line);

size_t	env_namelen(char *name)
{
	size_t	len;

	len = 0;
	if (name[0] == '$'
		|| name[0] == '?'
		|| name[0] == '0')
		return (1);
	while (name[len])
	{
		if (!ft_isalnum(name[len]) && name[len] != '_')
			return (len);
		len++;
	}
	return (len);
}

char	*expand_line(char *line)
{
	char	*ret;
	char	*varname;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && env_namelen(line + i + 1))
		{
			varname = ft_substr(line + i, 1, env_namelen(line + i + 1));
			ret = ft_strjoin_free(ret, env_lookup(varname), 1, 0);
			free(varname);
			i += env_namelen(line + i + 1) + 1;
		}
		else
			ret = ft_strjoin_free(ret, ft_substr(line + i++, 0, 1), 1, 1);
	}
	return (ret);
}

/// @brief insert a new chain of tokens after the current token
void	insert_token(t_token *token, t_token *new)
{
	t_token	*tmp;

	tmp = token->next;
	token->next = new;
	new->prev = token;
	while (new->next)
		new = new->next;
	new->next = tmp;
	if (tmp)
		tmp->prev = new;
}

void	tokens_expander(t_token	*token)
{
	t_token	*tmp1;
	t_token	*tmp2;

	while (token)
	{
		if (token->type & (TOK_VAR | TOK_DBLQ))
			token->token = expand_line(token->raw + (token->type == TOK_DBLQ));
		if (token->type == TOK_VAR)
		{
			tmp1 = tokenizer(token->token);
			tmp2 = tmp1;
			while (tmp1)
			{
				tmp1->type = TOK_LITERAL;
				tmp1 = tmp1->next;
			}
			insert_token(token, tmp2);
		}
		else
			token->token = ft_strdup(token->raw + (token->type == TOK_SNGQ));
		token = token->next;
	}
}

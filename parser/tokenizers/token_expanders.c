/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expanders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:21:50 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/23 16:43:54 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"
#include "t_token.h"

t_token	*tokenizer(char *line, bool subtok);

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



/// @brief  populate the ->token field of the tokens, 
///		tokens for DBLQ it replace $var with values, for the rest it just copy the line
/// 	removes quotes from DBLQ and SGLQ,
void	expand_literal_tokens(t_token	*token)
{
	while (token)
	{
		if (token->type == TOK_DBLQ)
			token->token = expand_line(token->raw + 1);
		else if (token->type & (TOK_LITERAL | TOK_SNGQ))
			token->token =ft_substr(token->raw,
				token->type == TOK_SNGQ, ft_strlen(token->raw) - 2 * (token->type == TOK_SNGQ));
		if (token->type & TOK_DBLQ)
			ft_strrchr(token->token, token->raw[0])[0] = '\0';
		token= token->next;
	}
}
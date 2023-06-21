/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expanders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:21:50 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/20 19:16:21 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"
#include "t_token.h"

/// @brief get the length of the variable name
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

/// @brief recreate a new line with variables expanded
char	*expand_line(char *line)
{
	char	*ret;
	char	*varname;
	char	*varvalue;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && env_namelen(line + i + 1))
		{
			varname = ft_substr(line + i, 1, env_namelen(line + i + 1));
			varvalue = env_lookup(varname);
			if (!varvalue)
				varvalue = "";
			ret = ft_strjoin_free(ret, varvalue, 1, 0);
			free(varname);
			i += env_namelen(line + i + 1) + 1;
		}
		else
			ret = ft_strjoin_free(ret, ft_substr(line + i++, 0, 1), 1, 1);
	}
	return (ret);
}

/// @brief check if the token is in a context of a file redirection
///    example: cat >$var"TOKEN"file	-> TOKEN is not expanded
int	is_in_file_ctx(t_token	*token)
{
	int	match;

	match = TOK_FILEIN | TOK_FILEOUT | TOK_FILEAPND;
	while (token->prev)
	{
		if (token->prev->type & match)
			return (1);
		else if (token->prev->type & (TOK_PIPE | TOK_HRDC)
			|| token->prev->space_after)
			return (0);
		token = token->prev;
	}
	return (0);
}

/// @brief expand literal tokens 
///        and populate the token->token field of tokens
///		 -# if quoted tokens are in file context;
///           they are not expanded nor stripped from quotes
///      -# quoted tokens are stripped from the quote characters.
///      -# Double quote characters are expanded unless in filename context.
///		 -# Expansion of variable tokens is kept till merging phase.
///        	because we need to know which context the variable is in
void	expand_literal_tokens(t_token	*token)
{
	while (token)
	{
		if (token->type & (TOK_SNGQ | TOK_DBLQ))
			token->type |= TOK_LITERAL;
		if (token->type & (TOK_DBLQ | TOK_SNGQ) && is_in_file_ctx(token))
		{
			token->token = ft_strdup(token->raw);
			token = token->next;
			continue ;
		}
		if (token->type & TOK_DBLQ)
			token->token = expand_line(token->raw + 1);
		else if (token->type & (TOK_LITERAL | TOK_SNGQ))
			token->token = ft_substr(token->raw,
					(token->type & TOK_SNGQ) == TOK_SNGQ,
					ft_strlen(token->raw) - 2 * (token->type == TOK_SNGQ));
		if (token->type & TOK_DBLQ)
			ft_strrchr(token->token, token->raw[0])[0] = '\0';
		token = token->next;
	}
}

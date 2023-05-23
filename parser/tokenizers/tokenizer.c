/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:55:13 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/21 15:15:48 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_tokenizers.h"

int	is_redirection(char *line)
{
	if (*line == '|')
		return (1);
	if (*line == '<' || *line == '>')
	{
		if (*(line + 1) == '<' || *(line + 1) == '>')
			return (2);
		return (1);
	}
	return (0);
}

t_token	*tokenizer(char *line, bool subtok)
{
	t_token	*tokens;
	int		skip;

	tokens = 0;
	while (line && *line)
	{
		skip = 1;
		if (!subtok && (*line == '\'' || *line == '"'))
			skip = split_quote(line, *line, &tokens);
		else if (!subtok && is_redirection(line))
			skip = split_redirection(line, is_redirection(line), &tokens);
		else if (!subtok && *line == '$')
			skip = split_dollar(line, &tokens);
		else if (*line != ' ')
			skip = split_literal(line, &tokens, subtok);
		line = line + skip;
	}
	return (tokens);
}

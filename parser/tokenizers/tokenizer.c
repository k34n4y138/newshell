/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:55:13 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/17 18:12:25 by zmoumen          ###   ########.fr       */
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

t_token	*tokenizer(char *line)
{
	t_token	*tokens;
	int		skip;

	tokens = 0;
	while (*line)
	{
		skip = 1;
		if (*line == '\'' || *line == '"')
			skip = split_quote(line, *line, &tokens);
		else if (is_redirection(line))
			skip = split_redirection(line,
					is_redirection(line), &tokens);
		else if (*line == '$')
			skip = split_dollar(line, &tokens);
		else if (*line != ' ')
			skip = split_literal(line, &tokens);
		line = line + skip;
	}
	return (tokens);
}



t_tokreport	syntaxify_tokens(t_token *tkn)
{
	t_tokreport	report;

	report = (t_tokreport){0, 0, 0};
	while (tkn)
	{
		// analyze tokens and generate report,
		// tokens expected after each token
		// Literal: any
		// var: any
		// <<: literal, var, sgqt, dqte,
		// <: literal, var, sgqt, dqte,
		// >>: literal, var, sgqt, dqte,
		// >: literal, var, sgqt, dqte,
		// |: literal, var, sgqt, dqte,
		// "": any, check if closed
		// '': any, check if closed
		tkn = tkn->next;
	}
	return (report);
}

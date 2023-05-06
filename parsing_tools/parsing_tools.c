/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:37:49 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/06 20:29:01 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"


int	append_token(t_token	*token, t_token **list);

int	split_quote(char	*line, char c, t_token **tokens);

int split_word(char *line, t_token **tokens);

int	split_dollar(char	*line, t_token **tokens)
{
	size_t	len;

	len = 0;
	while (line[len] == '$' || line[len] == '_' || ft_isalnum(line[len]))
		
		
	
}


int	is_redirection(char *line)
{
	if (*line == '<' || *line == '>')
	{
		if (*(line + 1) == '<' || *(line + 1) == '>')
			return (2);
		return (1);
	}
	return (0);
}

int	split_redirection(char	*line, t_token **tokens)
{
	int		skip;
	char	*redirection;

	skip = is_redirection(line);
	redirection = ft_substr(line, 0, skip);
	append_token(redirection, tokens);
	return (skip);
}

t_token	*tokenizer(char	*taskline)
{
	// split on dblqt
	// split on sglqt
	// split on <<, <, >>, >
	// split on $
	// check if token followed by space or not
	t_token	*tokens;
	size_t	skip;

	while(*taskline)
	{
		skip = 1;
		if (*taskline == '\'' || *taskline == '"')
			skip = split_till_lqt(taskline, *taskline, &tokens);
		else if (is_redirection(taskline))
			skip = split_redirection(taskline, &tokens);
		else if (*taskline == '$')
			skip = split_dollar(taskline, &tokens);
		else if (*taskline != ' ')
			skip = split_word(taskline, &tokens);
		taskline += skip;
	}
}

t_command	*parse_command(char	*line)
{
		
}
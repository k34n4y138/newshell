/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:37:49 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/08 20:06:13 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"
#include <stdio.h>

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
	tkn->len++;
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

int	split_literal(char *line, t_token **tokens)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	while (line[tkn->len] && !ft_strchr("'\"$<>| ", line[tkn->len]))
		tkn->len++;
	tkn->raw = ft_substr(line, 0, tkn->len);
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
	char	*redirection;
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	tkn->len = is_redirection(line);
	tkn->raw = ft_substr(line, 0, tkn->len);
	if (ft_strncmp(tkn->raw, "<<", 2) == 0)
		tkn->type = TOK_HRDC;
	else if (ft_strncmp(tkn->raw, ">>", 2) == 0)
		tkn->type = TOK_FILEAPND;
	else if (ft_strncmp(tkn->raw, "<", 1) == 0)
		tkn->type = TOK_FILEIN;
	else if (ft_strncmp(tkn->raw, ">", 1) == 0)
		tkn->type = TOK_FILEOUT;
	if (line[tkn->len] == ' ')
		tkn->space_after = true;
	append_token(tkn, tokens);
	return (tkn->len);
}

t_token	*tokenizer(char	*taskline)
{
	t_token	*tokens;
	size_t	skip;

	tokens = NULL;
	while (*taskline)
	{
		skip = 1;
		if (*taskline == '\'' || *taskline == '"')
			skip = split_quote(taskline, *taskline, &tokens);
		else if (is_redirection(taskline))
			skip = split_redirection(taskline, &tokens);
		else if (*taskline == '$')
			skip = split_dollar(taskline, &tokens);
		else if (*taskline != ' ')
			skip = split_literal(taskline, &tokens);
		taskline = taskline + skip;
	}
	return (tokens);
}

size_t	command_len(char	*line)
{
	int		qt_found;
	char	qt;
	size_t	len;

	qt_found = 0;
	len = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '"')
		{
			if (!qt_found)
			{
				qt_found = 1;
				qt = *line;
			}
			else if (qt == *line)
				qt_found = 0;
		}
		if (!qt_found && *line == '|')
			break ;
		line++;
		len++;
	}
	return (len);
}

t_command	*split_commands(char	*line)
{
	t_command	*cmd;
	t_command	*old;
	char		*rawcommand;

	old = NULL;
	while (*line)
	{
		rawcommand = ft_substr(line, 0, command_len(line));
		cmd = ft_calloc(1, sizeof(t_command));
		cmd->rawline = rawcommand;
		cmd->tokens = tokenizer(rawcommand);
		if (old)
		{
			old->next = cmd;
			cmd->prev = old;
		}
		line += ft_strlen(rawcommand);
		if (*line == '|')
			line++;
		old = cmd;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

t_command	*parse_commandline(char	*line)
{
	t_command	*cmd;

	cmd = split_commands(line);
	for (t_command *tmp = cmd; tmp; tmp = tmp->next)
	{
		printf("command: %s\n", tmp->rawline);
		for (t_token *tkn = tmp->tokens; tkn; tkn = tkn->next)
		{
			printf(">>> token: %s\n", tkn->raw);
		}
		printf("----------\n"); 
	}
	return (cmd);
}

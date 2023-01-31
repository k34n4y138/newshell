/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:55:17 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/31 20:14:54 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parsing_tools.h"
#include <stdbool.h>
#include <stdio.h>

int	get_validkeylen(char *line)
{
	char	*onechar;
	int		i;

	onechar = "$!@?#0-";
	i = 0;
	while (onechar[i++])
		if (onechar[i - 1] == *line)
			return (1);
	i = 0;
	while (
		(line[i] >= 'a' && line[i] <= 'z')
		|| (line[i] >= 'A' && line[i] <= 'Z')
		|| (line[i] == '_')
	)
		i++;
	return (i);
}

char	is_tasksplitter(char *s)
{
	if (!ft_strncmp(s, "||", 2))
		return (2);
	else if (!ft_strncmp(s, "&&", 2))
		return (2);
	else if (!ft_strncmp(s, "|", 1))
		return (1);
	return (0);
}

int	get_exectasklen(char *line)
{
	int		dblq_closed;
	int		sglq_closed;
	int		iter;

	dblq_closed = 1;
	sglq_closed = 1;
	iter = 0;
	while (line[iter])
	{
		if (line[iter] == '\'' && dblq_closed == 1)
			sglq_closed *= -1;
		else if (line[iter] == '"' && sglq_closed == 1)
			dblq_closed *= -1;
		else if (is_tasksplitter(line + iter)
			&& sglq_closed == 1 && dblq_closed == 1)
			return (iter + is_tasksplitter(line + iter));
		iter++;
	}
	if (dblq_closed == -1 || sglq_closed == -1)
		return (-1);
	return (iter);
}

void	append_rawtask(t_exectask **tasknodes, char *taskline)
{
	t_exectask	*newnode;
	t_exectask	*traverser;

	newnode = ft_calloc(1, sizeof(t_exectask));
	if (!newnode)
	{
		free(taskline);
		return ;
	}
	newnode->rawtask = taskline;
	traverser = *tasknodes;
	if (!traverser)
		*tasknodes = newnode;
	else
	{
		while (traverser->next)
			traverser = traverser->next;
		traverser->next = newnode;
		newnode->prev = traverser;
	}
}

t_exectask	*gen_tasks(char *line)
{
	int		count;
	int		lineln;
	int		lastret;
	t_exectask	*nodes;

	count = 0;
	lineln = 0;
	nodes = NULL;
	lastret = get_exectasklen(line + lineln);
	while (lastret > 0)
	{
		count++;
		append_rawtask(&nodes,
			ft_substr(line, lineln, lastret));
		lineln += lastret;
		lastret = get_exectasklen(line + lineln);
	}
	if (lastret == -1)
	{
		// destroy collected nodes;
		return (NULL);
	}
	return (nodes);
}

void	append_lexitoken(t_lexitoken **lexinodes, char *token, char nextchar)
{
	t_lexitoken	*newnode;
	t_lexitoken	*traverser;

	newnode = ft_calloc(1, sizeof(t_lexitoken));
	if (!newnode)
	{
		free(token);
		return ;
	}
	newnode->token = token;
	traverser = *lexinodes;
	if (nextchar == ' ')
		newnode->space_after = true;
	if (!traverser)
		*lexinodes = newnode;
	else
	{
		while (traverser->next)
			traverser = traverser->next;
		traverser->next = newnode;
		newnode->prev = traverser;
	}
}

char	is_redirection(char *s)
{
	if (!ft_strncmp(s, "<<", 2))
		return (2);
	else if (!ft_strncmp(s, "<", 1))
		return (1);
	else if (!ft_strncmp(s, ">>", 2))
		return (2);
	else if (!ft_strncmp(s, ">", 1))
		return (1);
	return (0);
}

char	*tokenize_till_quote(char	*line, char deli, int *to_append, int withquote)
{
	int len;
	// should STOP at delimiter. OR at ' OR " WHEN !withquote
	len = 1;
	while (line[len]
		&& (
			(line[len] != deli)
			|| (!withquote && (line[len] != '\'' || line[len] != '"'))
		))
		len++;
	if (withquote)
		len++;
	*to_append = len;
	return (ft_substr(line, 0, len));
}

int	lexical_tokenparsing(t_exectask *task)
{
	char	*taskline;
	char	*hld;
	int		to_appnd;

	while (task)
	{
		taskline = task->rawtask;
		while(*taskline)
		{
			to_appnd = 1;
			if (is_redirection(taskline) || is_tasksplitter(taskline))
			{
			to_appnd = is_redirection(taskline) | is_tasksplitter(taskline);
			hld = ft_substr(taskline,0,to_appnd);
			append_lexitoken(&task->rawtoken, hld, taskline[to_appnd]);
			}
			else if (*taskline=='\'' || *taskline=='"')
			{
				hld = tokenize_till_quote(taskline, *taskline, &to_appnd, 1);
				append_lexitoken(&task->rawtoken, hld, taskline[to_appnd]);
			}
			else if (*taskline == '$')
			{
				to_appnd = get_validkeylen(taskline + 1) + 1;
				hld = ft_substr(taskline, 0, to_appnd);
				append_lexitoken(&task->rawtoken, hld, taskline[to_appnd]);
			}
			else if (*taskline != ' ')
			{
				hld = tokenize_till_quote(taskline,' ', &to_appnd, 0);
				append_lexitoken(&task->rawtoken, hld, taskline[to_appnd]);
			}
			taskline += to_appnd;
		}
		task=task->next;
	}
	return (0);
}

t_exectask	*parse_commandline(char *line)
{
	t_exectask	*tasks;

	tasks = gen_tasks(line);
	if (!tasks)
		return (NULL);
	lexical_tokenparsing(tasks);
	while (tasks)
	{
		printf("line is: %s\n", tasks->rawtask);
		while (tasks->rawtoken)
		{
			printf("token: %s\n",tasks->rawtoken->token);
			tasks->rawtoken = tasks->rawtoken->next;
		}
		tasks = tasks->next;
	}
	return (tasks);
}

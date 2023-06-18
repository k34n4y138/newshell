/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:51 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/18 19:58:56 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "executer/exicution.h"
#include "env_tools/env_manager.h"
#include "parser/parser.h"
#include <stdlib.h>

void print_command(t_command *cmd)
{
	while (cmd)
	{
		printf("COMMAND: %s\n", cmd->argv[0]);
		printf("ARGC: %d\n", cmd->argc);
		for (int i = 0; i < cmd->argc; i++)
			printf("\t\tARG[%d]: %s\n", i, cmd->argv[i]);
		printf("REDIRECTS:\n");
		t_redirection *redirs = cmd->_redirects;
		while (redirs)
		{
			printf("\t\tREDIR: %d\n", redirs->type);
			printf("\t\tFILE: %s\n", redirs->file);
			redirs = redirs->next;
		}
		printf("+------------------------------------+\n");
		cmd = cmd->next;
	}
}


int	main(int argc, char **argv, char **environ)
{
	char		*line;
	t_command	*cmd;

	(void)argv;
	(void)argc;
	env_init(environ);
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break ;
		add_history(line);
		cmd = parse_command(line);
		// print_command(cmd);
		exicution(cmd);
		destroy_commands(cmd);
		free(line);
	}
	return (0);
}

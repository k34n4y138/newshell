/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:51 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/20 00:40:41 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "executer/execution.h"
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
		{;
			printf("\t\tFILE: %s\n", redirs->file);
			if (redirs->type & (REDIR_PIPEIN | REDIR_PIPEOUT))
				printf("\t\tis pipe %s\n", redirs->type & REDIR_PIPEIN ? "in" : "out");
			else if (redirs->type & REDIR_FILEIN)
				printf("\t\tis file in\n");
			else if (redirs->type & REDIR_FILEOUT)
				printf("\t\tis file out\n");
			else if (redirs->type & REDIR_FILEAPND)
				printf("\t\tis file append\n");
			else if (redirs->type & REDIR_HEREDOC)
				printf("\t\tis heredoc\n");
			if (redirs->type & FILE_CHECK_AMBIGOUS)
				printf("\t\tcheck if ambigous\n");
			if (redirs->type & REDIR_HEREDOC && redirs->type &HRDC_NO_EXPAND)
				printf("\t\tno expand\n");
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
		line = readline("minishell>$ ");
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

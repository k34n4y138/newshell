/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:12:28 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/22 09:49:51 by yowazga          ###   ########.fr       */
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

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		line = readline("minishell>$ ");
		if (!line)
			break ;
		add_history(line);
		cmd = parse_command(line);
		// print_command(cmd);
		if (cmd)
			execution(cmd);
		destroy_commands(cmd);
		free(line);
	}
	return (0);
}

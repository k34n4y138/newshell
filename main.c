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

void	signal_handler(int sig)
{
	(void)sig;
	env_exit_status(1, 1);
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
		if (cmd)
			execution(cmd);
		destroy_commands(cmd);
		free(line);
	}
	return (env_exit_status(0, 0));
}

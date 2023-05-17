/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:51 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/17 21:04:55 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include "env_tools/env_manager.h"
#include "parser/parser.h"
#include <stdlib.h>


int	main(int argc, char **argv, char **environ)
{
	char		*line;
	t_command	*cmd;

	env_init(environ);
	while (1)
	{
		line = readline("minishell >");
		printf("got: %s\n", line);
		if (!line)
			break ;
		cmd = parse_command(line);
		add_history(line);
		free(line);
	}
	return (0);
}


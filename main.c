/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:51 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/08 16:17:59 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "env_tools/env_manager.h"
#include "parsing_tools/parsing_tools.h"

int	main(int argc, char **argv, char **environ)
{
	char	*line;

	env_init(environ);
	while (1)
	{
		line = readline("minishell$ ");
		printf("got: %s\n", line);
		if (!line)
			break ;
		parse_commandline(line);
		add_history(line);
		free(line);
	}
	return (0);
}

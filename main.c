/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:51 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/25 10:59:17 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <readline/readline.h>
#include <stdio.h>
#include <sys/signal.h>
#include "parsing_tools/parsing_tools.h"


void	ignore_waa(int sig)
{
	(void)sig;
	write(0,"\n",1);
}

int	main(void)
{
	signal(SIGINT, ignore_waa);
	char *line;
	// int	len;
	while(1)
	{
		line = readline("\nminishell> ");
		add_history(line);
		parse_commandline(line);
	}
}
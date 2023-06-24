/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:53:41 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/24 10:53:42 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_argv(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '-' && av[i + 1] == 'n')
		{
			i++;
			while (av[i])
			{
				if (av[i] == 'n')
					i++;
				else
					return (1);
			}
		}
		else
			return (1);
	}
	return (0);
}

void	print_argv(t_command *cmd, int i)
{
	int	check;

	check = 0;
	if (i == 1)
		check = 1;
	while (cmd->argv[i])
	{
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (check)
		ft_printf_fd(1, "\n");
}

void	bltn_echo(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->argc == 1)
	{
		write(1, "\n", 1);
		exit(0);
	}
	while (cmd->argv[++i])
	{
		if (check_argv(cmd->argv[i]))
		{
			print_argv(cmd, i);
			break ;
		}
	}
	exit (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:20:26 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/21 12:16:17 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../parser/parser.h"

void	check_num_required(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[1][i])
	{
		if (cmd->argv[1][i] < '0' || cmd->argv[1][i] > '9')
		{
			ft_printf_fd(1, "exit\n");
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
					cmd->argv[1]);
			destroy_commands(cmd);
			exit(255);
		}
		i++;
	}
}

void	moor_arguments_1(t_command *cmd)
{
	int	status;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		exit(1);
	}
	waitpid(cmd->pid, &status, 0);
	env_exit_status(status >> 8, 1);
}

void	moor_arguments_2(void)
{
	ft_printf_fd(2, "minishell: exit: too many arguments\n");
	exit(1);
}

void	bltn_exit(t_command *cmd, int key)
{
	if (cmd->argc == 1)
	{
		ft_printf_fd(1, "exit\n");
		destroy_commands(cmd);
		exit(0);
	}
	check_num_required(cmd);
	if (cmd->argc != 2)
	{
		if (key == SINGL_EXIT)
			moor_arguments_1(cmd);
		else
			moor_arguments_2();
	}
	else
	{
		//9223372036854775807
		ft_printf_fd(1, "exit\n");
		exit(ft_atoi(cmd->argv[1]));
	}
}

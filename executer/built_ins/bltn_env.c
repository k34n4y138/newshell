/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:35:23 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/19 16:30:25 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/command_builders/t_command.h"
#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"

int	bltn_env(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->envp[i])
	{
		ft_putstr_fd(cmd->envp[i++], cmd->pip[1]);
		ft_putstr_fd("\n", cmd->pip[1]);
	}
	return (0);
}

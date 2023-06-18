/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:35:23 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/18 01:28:14 by zmoumen          ###   ########.fr       */
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
		ft_putstr_fd(cmd->envp[i++], cmd->io[1]);
		ft_putstr_fd("\n", cmd->io[1]);
	}
	return (0);
}

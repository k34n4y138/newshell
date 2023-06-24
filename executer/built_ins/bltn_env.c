/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:35:23 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/24 15:13:12 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/command_builders/t_command.h"
#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"

void	bltn_env(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->envp = env_export();
	while (cmd->envp[i])
	{
		ft_putstr_fd(cmd->envp[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	ft_putstr_fd("_=env\n", 1);
	exit(0);
}

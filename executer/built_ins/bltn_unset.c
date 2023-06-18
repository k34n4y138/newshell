/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:43:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/17 01:32:34 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../parser/command_builders/t_command.h"
#include "../../libft/libft.h"
#include "../../env_tools/env_manager.h"
#include "stdio.h"

int	bltn_unset(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!env_validate_key(cmd->argv[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				cmd->argv[i]);
			return (1);
		}
		env_delete(cmd->argv[i]);
		i++;
	}
	return (0);
}

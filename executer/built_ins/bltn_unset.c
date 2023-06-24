/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 22:43:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/21 20:16:59 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/command_builders/t_command.h"
#include "../../libft/libft.h"
#include "../../env_tools/env_manager.h"
#include "stdio.h"

int	bltn_unset(t_command *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (!env_validate_key(cmd->argv[i]))
		{
			ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n",
				cmd->argv[i++]);
			ret = 1;
			continue ;
		}
		env_delete(cmd->argv[i++]);
	}
	if (cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT))
		exit(ret);
	env_exit_status(ret, 1);
	return (ret);
}

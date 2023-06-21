/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:15:12 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/21 10:47:49 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/command_builders/t_command.h"
#include "../../libft/libft.h"
#include "../../env_tools/env_manager.h"
#include <stdio.h>

void	print_args()
{
	t_envirun	*env;
	env = *env_store(0);
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

int	add_env(char *line, int set)
{
	char	*key;
	char	*value;

	value = NULL;
	if (ft_strchr(line, '='))
	{
		value = ft_strdup(ft_strchr(line, '=') + 1);
		key = ft_substr(line, 0, ft_strlen(line) - ft_strlen(value) - 1);
	}
	else
		key = ft_strdup(line);
	if (env_validate_key(key))
	{
		if (set)
			env_update(key, value, 1);
	}
	else
		ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", line);
	free(key);
	free(value);
	return (1);
}

void	bltn_export(t_command *cmd)
{
	int	i;
	int	lnret;
	int	ret;

	ret = 0;
	if (cmd->argc == 1)
		print_args();
	else
	{
		i = 1;
		while (i < cmd->argc)
		{
			lnret = add_env(cmd->argv[i++],
					!(cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT)));
			if (lnret)
				ret = lnret;
		}
	}
	if (cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT))
		exit(ret);
	env_exit_status(ret, 1);
}

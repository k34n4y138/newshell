/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:15:12 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/23 21:31:27 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/command_builders/t_command.h"
#include "../../libft/libft.h"
#include "../../env_tools/env_manager.h"
#include <stdio.h>

void	print_args(void)
{
	t_envirun	*env;

	env = *env_store(0);
	while (env)
	{
		ft_printf_fd(1, "declare -x %s", env->key);
		if (env->value)
			ft_printf_fd(1, "=\"%s\"", env->value);
		ft_printf_fd(1, "\n");
		env = env->next;
	}
}

int	iden_not_valid(char	*line, char *key, char *value)
{
	ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", line);
	free(key);
	free(value);
	return (1);
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
		return (iden_not_valid(line, key, value));
	free(key);
	free(value);
	return (0);
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

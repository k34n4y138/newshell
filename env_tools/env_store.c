/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:51:42 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/24 15:06:26 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "env_manager.h"
#include <unistd.h>

t_envirun	**env_store(int destroy)
{
	static t_envirun	*env = NULL;

	if (destroy && env)
	{
		while (env)
		{
			free(env->key);
			free(env->value);
			free(env);
			env = env->next;
		}
	}
	return (&env);
}

void	set_mandatory_envs(void)
{
	char	*tmpwd;

	env_update("OLDPWD", NULL, 1);
	tmpwd = getcwd(NULL, 0);
	env_update("PWD", tmpwd, 1);
	free(tmpwd);
	if (env_lookup("SHLVL"))
	{
		tmpwd = ft_itoa(ft_atoi(env_lookup("SHLVL")) + 1);
		env_update("SHLVL", tmpwd, 1);
		free(tmpwd);
	}
	else
		env_update("SHLVL", "1", 1);
	env_delete("_");
}

void	env_init(char	**initenv)
{
	t_envirun	**env;
	t_envirun	*traverser;
	t_envirun	*tmp;

	env = env_store(0);
	traverser = *env;
	while (initenv && *initenv)
	{
		tmp = ft_calloc(sizeof(t_envirun), 1);
		tmp->value = ft_strdup(ft_strchr(*initenv, '=') + 1);
		tmp->key = ft_substr(*initenv, 0,
				ft_strlen(*initenv) - ft_strlen(tmp->value) - 1);
		if (!traverser)
			*env = tmp;
		else
			traverser->next = tmp;
		traverser = tmp;
		initenv++;
	}
	set_mandatory_envs();
}

int	env_exit_status(int status, int set)
{
	static int	exit_status = 0;

	if (set)
		exit_status = status;
	return (exit_status);
}

int	env_validate_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(*key) && *key != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

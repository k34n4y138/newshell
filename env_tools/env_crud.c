/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:00:15 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/14 22:30:52 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_manager.h"
#include "../libft/libft.h"

int	env_insert(char	*key, char *value)
{
	t_envirun	**env;
	t_envirun	*traverser;
	t_envirun	*new_env;

	env = env_store(0);
	new_env = ft_calloc(sizeof(t_envirun), 1);
	new_env->key = ft_strdup(key);
	if (value)
		new_env->value = ft_strdup(value);
	if (!*env)
		*env = new_env;
	else
	{
		traverser = *env;
		while (traverser->next)
			traverser = traverser->next;
		traverser->next = new_env;
	}
	return (0);
}

char	*env_lookup(char *key)
{
	t_envirun	*env;

	env = *env_store(0);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

int	env_update(char	*key, char	*value, int create)
{
	t_envirun	*env;

	env = *env_store(0);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (value)
			{
				free(env->value);
				env->value = ft_strdup(value);
			}
			return (0);
		}
		env = env->next;
	}
	if (create)
		env_insert(key, value);
	return (1);
}

int	env_delete(char	*key)
{
	t_envirun	*crnt;
	t_envirun	*prev;

	crnt = *env_store(0);
	prev = NULL;
	while (crnt)
	{
		if (!ft_strcmp(crnt->key, key))
		{
			if (prev)
				prev->next = crnt->next;
			else
				*env_store(0) = crnt->next;
			free(crnt->key);
			free(crnt->value);
			free(crnt);
			return (0);
		}
		prev = crnt;
		crnt = crnt->next;
	}
	return (-1);
}

char	**env_export(void)
{
	t_envirun	*env;
	char		**export;
	int			i;

	env = *env_store(0);
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	export = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	env = *env_store(0);
	while (env)
	{
		export[i] = ft_strjoin(env->key, "=");
		export[i] = ft_strjoin_free(export[i], env->value, 1, 0);
		i++;
		env = env->next;
	}
	return (export);
}

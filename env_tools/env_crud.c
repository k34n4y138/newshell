/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:00:15 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/08 17:36:10 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_manager.h"
#include "../libft/libft.h"

int	env_insert(char *key, char *value)
{
	char	***env;
	char	**new_env;
	char	*new_value;
	int		envsize;

	env = env_store(0);
	envsize = 0;
	new_value = ft_strjoin_free(ft_strjoin(key, "="), value, 1, 0);
	while (env[0][envsize])
		envsize++;
	new_env = ft_calloc(sizeof(char *), envsize + 2);
	ft_memcpy(new_env, *env, sizeof(char *) * envsize);
	new_env[envsize] = new_value;
	free(*env);
	*env = new_env;
	return (0);
}

int	keycmp(char *env, char *key)
{
	int	keylen;

	keylen = ft_strlen(key);
	if (ft_strncmp(env, key, keylen) == 0 && env[keylen] == '=')
		return (1);
	return (0);
}

char	*env_lookup(char *key)
{
	char	**env;
	int		i;
	int		keylen;

	env = *env_store(0);
	i = 0;
	keylen = ft_strlen(key);
	while (env[i])
	{
		if (keycmp(env[i], key))
			return (env[i] + keylen + 1);
		i++;
	}
	return ("");
}

int	env_update(char *key, char *value)
{
	char	**env;
	char	*new_value;

	env = *env_store(0);
	while (*env)
	{
		if (keycmp(*env, key))
		{
			new_value = ft_strjoin_free(ft_strjoin(key, "="), value, 1, 0);
			free(*env);
			*env = new_value;
			return (0);
		}
		env++;
	}
	env_insert(key, value);
	return (1);
}

int	env_delete(char *key)
{
	int		envsize;
	int		newenvsize;
	char	***env;
	char	**new_env;

	if (env_lookup(key) == NULL)
		return (1);
	env = env_store(0);
	envsize = 0;
	while (env[0][envsize])
		envsize++;
	new_env = ft_calloc(sizeof(char *), envsize);
	envsize = 0;
	newenvsize = 0;
	while (env[0][envsize])
	{
		if (keycmp(env[0][envsize], key))
			new_env[newenvsize++] = env[0][envsize++];
		else
			free(env[0][envsize++]);
	}
	free(*env);
	*env = new_env;
	return (0);
}

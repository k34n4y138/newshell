/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:51:42 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/10 15:35:37 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	***env_store(int destroy)
{
	static char	**env = NULL;
	int			i;

	i = 0;
	if (destroy && env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
		env = NULL;
	}
	return (&env);
}

int	env_exit_status(int status, int set)
{
	static int	exit_status = 0;

	if (set)
		exit_status = status;
	return (exit_status);
}

char	**env_init(char **initenv)
{
	char	**env;
	int		i;
	int		size;

	size = 0;
	while (initenv[size])
		size++;
	i = 0;
	env = ft_calloc(sizeof(char *), size + 1);
	while (i < size)
	{
		env[i] = ft_strdup(initenv[i]);
		i++;
	}
	env[i] = NULL;
	*env_store(0) = env;
	return (env + 1);
}

void	env_destroy(void)
{
	env_store(1);
}

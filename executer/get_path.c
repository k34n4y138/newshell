/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:20:53 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/18 18:17:55 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exicution.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*check_p(char *cmd)
{
	char	*valid;

	valid = NULL;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			valid = ft_strdup(cmd);
		else
		{
			ft_printf("minishell: permission denied: %s\n", cmd);
			exit (126);
		}
	}
	return (valid);
}

char	*check_env(char **env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strdup(ft_strchr(env[i], '=') + 1);
			break ;
		}
		i++;
	}
	if (!path)
		path = ft_strdup(PATH);
	return (path);
}

char	*get_valid_path(char *path, char *cmd0)
{
	char	**paths;
	char	*valid;
	int		i;

	i = -1;
	valid = NULL;
	paths = NULL;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], cmd0);
		if (access(paths[i], F_OK) == 0)
		{
			valid = ft_strdup(paths[i]);
			break ;
		}
	}
	free(path);
	free_paths(paths);
	return (valid);
}


char	*get_path(char **env, char *cmd0, int status)
{
	char	*path;
	char	*valid_path;

	valid_path = NULL;
	if (status == 0)
	{
		path = check_env(env);
		valid_path = get_valid_path(path, cmd0);
		if (!valid_path)
		{
			ft_printf("minishell: %s: command not found\n", cmd0);
			exit(127);
		}	
	}
	else if (status == 1)
	{
		valid_path = check_p(cmd0);
		if (!valid_path)
		{
			ft_printf("minishell: %s: no such file or directory\n", cmd0);
			exit(127);
		}
	}
	return (valid_path);
}
